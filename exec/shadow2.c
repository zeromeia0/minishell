/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:17:50 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/20 13:49:09 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	heredoc_setup(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	signal(SIGINT, sig_handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	write_heredoc_line(char *str, int fd[2])
{
	char	*expanded;

	if (!fd || !str)
		return ;
	if (btree()->cmds && btree()->cmds->infiles
		&& btree()->cmds->infiles->flag == 0)
		expanded = expand_hd(str);
	else
		expanded = str;
	write(fd[1], expanded, ft_strlen(expanded));
	write(fd[1], "\n", 1);
	if (expanded != str)
		free(expanded);
}

void	process_heredoc_lines(char *delimiter, int len, int fd[2])
{
	char	*str;

	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, len + 1))
	{
		write_heredoc_line(str, fd);
		free(str);
		if (btree()->global_signal == 130)
			megalodon_giga_chad_exit(130, 0);
		str = readline("> ");
	}
	if (!str && btree()->global_signal != 130)
	{
		ft_putstr_fd("warning: here-document \
			delimited by end-of-file (wanted `",
			STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
	free(str);
}

void	setup_signals_for_parent(void)
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_child(t_infile *in, int *p)
{
	signal(SIGINT, sig_handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(p[0]);
	get_single_heredoc(in->file, p);
	close(p[1]);
	megalodon_giga_chad_exit(0, 0);
}
