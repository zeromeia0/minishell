/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:43:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/03 14:40:24 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "minishell.h"

void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	int	heredoc_fd;

	heredoc_fd = get_heredoc_fd(cmd);
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (first_fd != -1 && cmd->infiles == NULL && heredoc_fd == -1)
	{
		dup2(first_fd, STDIN_FILENO);
		close(first_fd);
	}
	if (cmd->next != NULL && cmd->outfiles == NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

void	execute_child(t_cmds *cmd, int first_fd, int fd[2], char **env)
{
	char	**cleaned_cmd;

	cleaned_cmd = array_to_exec(cmd);
	if (has_redir(cmd))
		exec_redirections(cmd, env, cleaned_cmd, 0);
	setup_child_fds(first_fd, fd, cmd);
	execute_child_helper(cleaned_cmd, env, cmd);
}

int	setup_pipe(t_cmds *cmd, int *first_fd, int fd[2])
{
	(void)first_fd;
	if (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
	}
	return (0);
}

int	process_command_helper(t_cmds *cmd, int prev_fd, char **env)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (setup_pipe(cmd, &prev_fd, fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		execute_child(cmd, prev_fd, fd, env);
	if (prev_fd >= 0)
		close(prev_fd);
	if (cmd->next != NULL)
	{
		if (fd[1] >= 0)
			close(fd[1]);
		return (fd[0]);
	}
	else
		return (file_descriptor_closer(fd), -1);
}

int	process_command(t_cmds *cmd, int *first_fd, char **env)
{
	int	new_fd;

	if (cmd->cmd == NULL)
		return (cmd->flag_to_exec = 1, 0);
	if (cmd->flag_to_exec == 0)
	{
		new_fd = process_command_helper(cmd, *first_fd, env);
		*first_fd = new_fd;
	}
	return (0);
}
