/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:40:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/13 09:52:26 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	double_helper(int status, int p[2], pid_t pid)
{
	close(p[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
}

int	check_cmds(t_cmds *cmds, char **args, char **envp)
{
	t_cmds	*current;

	if (!cmds || !cmds->cmd)
		return (1);
	current = cmds;
	while (current)
	{
		if (!is_cmd_valid(current, args, envp))
			return (127);
		current = current->next;
	}
	return (1);
}

int	super_checker_goated(t_cmds *cmd, char **command, char **args)
{
	(void)command;
	if (!has_builtin(cmd) && !has_redir(cmd)
		&& !is_system_path_command(cmd->cmd[0], args))
	{
		if (ft_strchr(cmd->cmd[0], '/'))
			handle_absolute_path_cmd(cmd->cmd[0], args, args);
		return (1);
	}
	return (0);
}

int	exec_single_cmd(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd)
		return (btree()->exit_status);
	if (cmd->flag_to_exec == 1)
		return (btree()->exit_status);
	if (has_builtin(cmd) && !has_redir(cmd))
		return (exec_single_cmd_aux(cmd));
	prepare_signals_and_fork(cmd);
	return (btree()->exit_status);
}

int	check_helper(t_cmds *cmd, int *please)
{
	int	r;

	while (cmd)
	{
		if (cmd->heredoc_done == 0 && *please == 0)
		{
			*please = 1;
			r = handle_heredoc(cmd);
			if (r != 0)
			{
				cmd->flag_to_exec = 1;
				cmd->heredoc_done = 1;
				return (-1);
			}
			cmd->heredoc_done = 1;
		}
		cmd = cmd->next;
	}
	return (0);
}
