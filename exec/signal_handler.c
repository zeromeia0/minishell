/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/23 22:32:39 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	// printf("HANDLE SIGINT\n");
	btree()->exit_status = 130;
	btree()->global_signal = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void set_to_onethirty(int sig)
{
	(void)sig;
	// printf("set one trusht\n");

	btree()->global_signal = 130;
	rl_replace_line("", 0);
}

void	handle_heredoc(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	// printf("HANDLE heredoc\n");

	close(0);
	btree()->global_signal = 130;
}

void handle_quit(int sig)
{
	(void)sig;
	printf("control d\n");
	signal(SIGQUIT, SIG_IGN);
	close(0);
}

int restart_signals(void)
{
	// printf("restart\n");
	if (btree()->global_signal == 130)
		{write (1, "\n", 1);
			btree()->global_signal = 130;}
	signal(SIGINT, handle_sigint);
	btree()->global_signal = 0;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	return (0);
}