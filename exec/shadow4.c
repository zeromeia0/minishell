/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:20:04 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/12 23:20:06 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	reset_heredoc_flags(t_binary *tree)
{
	t_cmds	*cmd;

	if (!tree)
		return ;
	cmd = tree->cmds;
	while (cmd)
	{
		cmd->heredoc_done = 0;
		cmd = cmd->next;
	}
	reset_heredoc_flags(tree->left);
	reset_heredoc_flags(tree->right);
}

void	help_to_process(t_cmds *cmd, int p[2])
{
	close(p[0]);
	printf("pipes\n");
	signal(SIGINT, sig_handle_heredoc);
	process_all_heredocs(cmd->infiles, p);
	close(p[1]);
	megalodon_giga_chad_exit(0, 0);
}
