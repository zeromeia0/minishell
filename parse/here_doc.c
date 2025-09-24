/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:09:07 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 20:18:58 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	count_heredocs(t_infile *in)
{
	int	count;

	count = 0;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			count++;
		in = in->next;
	}
	return (count);
}

void	here_doc_loop(char *str, char *delimiter, int len, int *fd)
{
	char	*expanded;

	while (str && ft_strncmp(str, delimiter, len + 1))
	{
		if (fd)
		{
			expanded = expand(str, 0, 0, 1);
			write(fd[1], expanded, ft_strlen(expanded));
			write(fd[1], "\n", 1);
			if (expanded != str)
				free(expanded);
		}
		free(str);
		if (btree()->global_signal == 130)
			exit(130);
		str = readline("> ");
	}
}

void	get_single_heredoc(char *eof, int fd[2])
{
	char	*str;
	char	*delimiter;
	int		len;
	int		tty_fd;

	delimiter = remove_aspas(eof);
	len = ft_strlen(delimiter);
	if (btree()->global_signal == 130)
		exit(130);
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("> ");
	here_doc_loop(str, delimiter, len, fd);
	if (!str && btree()->global_signal != 130)
		fprintf(stderr,
			"warning: here-document delimited by end-of-file (wanted `%s')\n",
			delimiter);
	free(str);
	free(delimiter);
}

void	process_heredoc_recursive_simple(t_infile *current, int fd[2])
{
	if (!current)
		return ;
	if (ft_strcmp(current->token, "<<") == 0)
	{
		get_single_heredoc(current->file, fd);
	}
	process_heredoc_recursive_simple(current->next, fd);
}

void	process_all_heredocs(t_infile *in, int fd[2])
{
	process_heredoc_recursive_simple(in, fd);
}
