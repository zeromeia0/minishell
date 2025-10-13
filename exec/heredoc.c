/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:11:44 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/13 10:03:05 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	get_single_heredoc(char *eof, int fd[2])
{
	char	*delimiter;
	int		len;

	if (!eof)
		return ;
	if (btree()->global_signal == 130)
		megalodon_giga_chad_exit(130, 0);
	delimiter = remove_aspas(eof);
	len = ft_strlen(delimiter);
	heredoc_setup();
	process_heredoc_lines(delimiter, len, fd);
	free(delimiter);
	if (fd)
		close(fd[1]);
}

void	process_all_heredocs(t_infile *in, int p[2])
{
	t_infile	*current;
	int			tmp_pipe[2];

	current = in;
	while (current)
	{
		if (ft_strcmp(current->token, "<<") == 0 && in->file)
		{
			if (pipe(tmp_pipe) == -1)
			{
				perror("pipe");
				exit(1);
			}
			get_single_heredoc(current->file, tmp_pipe);
			close(tmp_pipe[1]);
			current->heredoc_fd = tmp_pipe[0];
		}
		current = current->next;
	}
}

int	handle_heredoc_parent(t_infile *in, pid_t pid, int *p)
{
	int	status;

	close(p[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || (WIFEXITED(status)
			&& WEXITSTATUS(status) == 130))
	{
		close(p[0]);
		btree()->global_signal = 130;
		btree()->exit_status = 130;
		restart_signals();
		return (-1);
	}
	restart_signals();
	in->heredoc_fd = p[0];
	return (0);
}

int	process_heredoc_for_infile(t_infile *in)
{
	int		p[2];
	pid_t	pid;
	if (ft_strcmp(in->token, "<<") != 0)
		return (0);
	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		handle_heredoc_child(in, p);
	else
		return (handle_heredoc_parent(in, pid, p));
	return (0);
}

int	manage_heredocs(t_cmds *cmd)
{
	t_cmds		*cur;
	t_infile	*in;
	printf("managng heredoc\n");
	if (!cmd)
		return (-1);
	setup_signals_for_parent();
	cur = cmd;
	while (cur)
	{
		if (cur->heredoc_done == 1)
			return (0);
		in = cur->infiles;
		while (in)
		{
			if (process_heredoc_for_infile(in) == -1)
				return (-1);
			in = in->next;
		}
		cur->heredoc_done = 1;
		cur = cur->next;
	}
	return (0);
}
