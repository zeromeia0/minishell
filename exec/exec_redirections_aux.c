/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:05:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/13 10:03:51 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	handle_heredoc(t_cmds *cmd)
{
	if (!cmd || cmd->heredoc_done)
		return (0);
	signal(SIGINT, handle_sigint);
	if (cmd->heredoc_done == 1)
		return (0);
	if (manage_heredocs(cmd) < 0)
		return (-1);
	cmd->heredoc_done = 1;
	return (0);
}

int	handle_regular_redirections(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<") == 0)
		{
			if (exec_single_left(in) < 0)
				return (1);
		}
		in = in->next;
	}
	if (exec_out_redirections(cmd->outfiles) < 0)
		return (-1);
	return (0);
}
