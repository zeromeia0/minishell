/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:19:21 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/23 22:43:43 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	if (first_fd != -1)
		dup2(first_fd, STDIN_FILENO);
	if (has_redir(cmd))
		exec_redirections(cmd);
	else if (cmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (first_fd != -1)
		close(first_fd);
}

void	execute_child(t_cmds *cmd, int first_fd, int fd[2], char **env)
{
	char	**cleaned_cmd;
	int		status;

	setup_child_fds(first_fd, fd, cmd);
	
	if (has_redir(cmd))
		exec_redirections(cmd);
	cleaned_cmd = array_to_exec(cmd);
	
	if (!cleaned_cmd || !cleaned_cmd[0])
	{
		write(2, "cmd is empty\n", 14);
		free_matrix(cleaned_cmd);
		exit(127); // Command not found
	}
	
	if (is_builtin(cleaned_cmd[0]))
	{
		status = exec_builtin(cleaned_cmd[0], cleaned_cmd, env);
		free_matrix(cleaned_cmd);
		exit(status);
	}
	else
	{
		exec_path(cleaned_cmd[0], cleaned_cmd, env);
		free_matrix(cleaned_cmd);
		exit(127); // Command not found
	}
}

int	setup_pipe(t_cmds *cmd, int *first_fd, int fd[2])
{
	if (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
	}
	return (0);
}

static int	process_command(t_cmds **cmd, int *first_fd, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (setup_pipe(*cmd, first_fd, fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		execute_child(*cmd, *first_fd, fd, env);
	if (*first_fd != -1)
		close(*first_fd);
	if ((*cmd)->next != NULL)
	{
		close(fd[1]);
		*first_fd = fd[0];
	}
	*cmd = (*cmd)->next;
	return (0);
}

int	has_heredocs(t_cmds *cmd)
{
	t_infile *in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			return (1);
		in = in->next;
	}
	return (0);
}
int	process_command_heredocs(t_cmds *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;

	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		signal(SIGINT, handle_heredoc);
		process_all_heredocs(cmd->infiles, p);
		close(p[1]);
		exit(0);
	}
	else
	{
		close(p[1]);
		waitpid(pid, &status, 0);
		close(p[0]); // We don't use the output for now
		
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (-1);
	}
	return (0);
}

int	exec_pipes(t_cmds *cmd, char **env)
{
	int		first_fd;
	int		status;
	t_cmds	*current;

	// Process ALL heredocs for ALL commands in the pipe first
	current = cmd;
	while (current)
	{
		if (has_heredocs(current))
		{
			if (process_command_heredocs(current) < 0)
				return (-1);
		}
		current = current->next;
	}

	// Now set up and execute the pipes
	first_fd = -1;
	if (!cmd || cmd->cmd[0] == NULL)
		return (0);
	
	current = cmd;
	while (current)
	{
		if (process_command(&current, &first_fd, env) == -1)
			return (-1);
	}
	
	while (wait(&status) > 0)
		;
	
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 128 + WTERMSIG(status);
	
	return (btree()->exit_status);
}
