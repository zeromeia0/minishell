/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:12:18 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/07 07:07:32 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	handle_parent(pid_t pid, int shell_should_ignore)
{
	int	status;

	if (!shell_should_ignore)
		signal(SIGINT, set_to_onethirty);
	waitpid(pid, &status, 0);
	// printf("restarting signal 1\n"), restart_signals();
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 130;
}

void	prepare_signals_and_fork(t_cmds *cmd)
{
	pid_t	pid;
	int		shell_should_ignore;

	shell_should_ignore = 0;
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	if (cmd_has_heredoc(cmd))
	{
		shell_should_ignore = 1;
		signal(SIGINT, SIG_IGN);
	}
	pid = fork();
	if (pid == 0)
		exec_child(cmd);
	else
		handle_parent(pid, shell_should_ignore);
}

int	exec_subshell(t_binary *subshell, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		children_killer(exec_tree(subshell, args, envp));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 128 + WTERMSIG(status);
	return (btree()->exit_status);
}

int	cmd_has_heredoc(t_cmds *cmd)
{
	t_infile	*in;

	in = NULL;
	if (!cmd)
		return (0);
	in = cmd->infiles;
	while (in)
	{
		if (in->token && ft_strcmp(in->token, "<<") == 0)
			return (1);
		in = in->next;
	}
	return (0);
}

int	check_outfiles(t_cmds *cmds)
{
	t_outfile	*current_outfile;

	if (!cmds || !cmds->outfiles)
		return (1);
	current_outfile = cmds->outfiles;
	while (current_outfile)
	{
		if (ensure_outfile(current_outfile) < 0)
			return (0);
		current_outfile = current_outfile->next;
	}
	return (1);
}
