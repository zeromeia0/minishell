/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:43:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/25 14:25:38 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	char	**cleaned_cmd;
	int		status;

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
		free_matrix(cleaned_cmd);
		exit(127);
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
		exit(127);
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

int	process_command(t_cmds *cmd, int *first_fd, char **env)
{
	int		fd[2];
	pid_t	pid;

	// fprintf(stderr, "PUTTING THE FLAG exec\n");
	
	if (cmd->cmd == NULL)
		cmd->flag_to_exec = 1;
	// fprintf(stderr, "PUTTING THE FLAG exec 2\n");
	if (cmd->flag_to_exec == 0)
	{
		if (setup_pipe(cmd, first_fd, fd) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
			execute_child(cmd, *first_fd, fd, env);
		if (*first_fd != -1)
			close(*first_fd);
		if ((cmd)->next != NULL)
		{
			close(fd[1]);
			*first_fd = fd[0];
		}
	}
	return (0);
}

int	has_heredocs(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			return (1);
		in = in->next;
	}
	return (0);
}
