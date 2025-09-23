/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/23 22:53:14 by vvazzs           ###   ########.fr       */
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
	// printf("HANDLE heredoc\n");
	
	signal(SIGINT, SIG_DFL);
	btree()->global_signal = 130;
	exit(130);
}

void handle_quit(int sig)
{
	(void)sig;
	// printf("control d\n");
	signal(SIGQUIT, SIG_IGN);
	// close(0);
}

int restart_signals(void)
{
    if (btree()->global_signal == 130)
        btree()->global_signal = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT in main shell
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
    return (0);
}