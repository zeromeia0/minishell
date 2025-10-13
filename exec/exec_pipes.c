/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:19:21 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/13 10:04:29 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	process_command_heredocs(t_cmds *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;

	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
		help_to_process(cmd, p);
	else
	{
		close(p[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		close(p[0]);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (btree()->exit_status = 130, -1);
	}
	return (0);
}

int	process_heredocs_and_checks(t_cmds *cmd)
{
	t_cmds	*current;

	current = cmd;
	while (current)
	{
		if (has_heredocs(current))
		{
			if (manage_heredocs(current) < 0)
			{
				btree()->exit_status = 130;
				return (btree()->exit_status);
			}
		}
		current = current->next;
	}
	if (btree()->global_signal == 130)
		return (130);
	return (0);
}

int	prepare_all_heredocs(t_cmds *cmd)
{
	t_cmds	*current;
	int		r;

	current = cmd;
	while (current)
	{
		if (!current->heredoc_done)
		{
			r = handle_heredoc(current);
			if (r != 0)
				return (r);
			current->heredoc_done = 1;
		}
		current = current->next;
	}
	return (0);
}

int	exec_pipes_helper(t_cmds *cmd, char **env, int *first_fd)
{
	t_cmds	*current;

	current = cmd;
	while (current)
	{
		if (process_command(current, first_fd, env) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	exec_pipes(t_cmds *cmd, char **env)
{
	int	first_fd;
	int	status;

	first_fd = -1;
	if (manage_heredocs(cmd) != 0)
		return (btree()->exit_status);
	if (exec_pipes_helper(cmd, env, &first_fd) == -1)
		return (-1);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 128 + WTERMSIG(status);
	if (btree()->env)
	{
		ft_free_matrix(btree()->env);
		btree()->env = list_to_char(*get_env_list());
	}
	return (btree()->exit_status);
}
