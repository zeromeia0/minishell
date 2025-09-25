/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/25 12:36:46 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

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

void	handle_heredoc(int sig)
{
	(void)sig;
	btree()->global_signal = 130;
	btree()->exit_status = 130;
	write(1, "\n", 1);
	exit(130);
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
