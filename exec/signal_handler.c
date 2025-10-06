/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/06 15:53:55 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	btree()->exit_status = 130;
	btree()->global_signal = 130;
	write(1, "\n", 1);
	if (btree()->global_signal != 131)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_to_onethirty(int sig)
{
	(void)sig;
	btree()->global_signal = 130;
	rl_replace_line("", 0);
}

void	sig_handle_heredoc_main(int sig)
{
	(void)sig;
	btree()->global_signal = 130;
	btree()->exit_status = 130;
	write(1, "\n", 1);
}


void	sig_handle_heredoc(int sig)
{
	(void)sig;
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	btree()->global_signal = 130;
	btree()->exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();       // tell readline the cursor is on a new line
	rl_replace_line("", 0); // clear any leftover input
	// rl_redisplay();         // refresh prompt (so ^C isn’t glued to prompt)
	megalodon_giga_chad_exit(130);
}


void	handle_quit(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
}

int	restart_signals(void)
{
	if (btree()->global_signal == 130)
		btree()->global_signal = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
