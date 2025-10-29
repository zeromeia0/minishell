/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:05:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 16:27:42 by vivaz-ca         ###   ########.fr       */
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

