/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:11:44 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/27 16:53:14 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	get_single_heredoc(char *eof, int fd[2])
{
	char	delimiter[4096];
	int		len;
	int prev_len;
	int result;
	
	if (!eof)
		return ;
	result = 0;
	if (btree()->global_signal == 130)
		megalodon_giga_chad_exit(130, 0);
	rm_quote(delimiter, eof);
	len = ft_strlen(delimiter);
	prev_len = ft_strlen(eof);
	if (len != prev_len)
		result = 1;
	heredoc_setup();
	process_heredoc_lines(delimiter, len, fd, result);
	if (btree()->env)
		ft_free_matrix(btree()->env);
	if (fd)
		close(fd[1]);
}

void	process_all_heredocs(t_infile *in, int p[2])
{
	t_infile	*current;
	int			tmp_pipe[2];

	(void)p;
	current = in;
	while (current)
	{
		if (ft_strcmp(current->token, "<<") == 0 && in->file)
		{
			if (pipe(tmp_pipe) == -1)
			{
				perror("pipe");
				megalodon_giga_chad_exit(1, 0);
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
