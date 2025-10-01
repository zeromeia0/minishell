/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:08:05 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/01 14:09:24 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <signal.h>
#include <stdio.h>

char	**array_to_exec(t_cmds *cmd)
{
	int		i;
	int		j;
	char	**new_argv;

	i = 0;
	j = 0;
	if (!cmd || !cmd->cmd)
		return (NULL);
	new_argv = malloc(sizeof(char *) * (count_tokens(cmd) + 1));
	if (!new_argv)
		return (NULL);
	while (cmd->cmd[i])
	{
		if (is_redir_token(cmd->cmd[i]) && cmd->cmd[i + 1])
			i += 2;
		else
			new_argv[j++] = strdup(cmd->cmd[i++]);
	}
	new_argv[j] = NULL;
	return (new_argv);
}

int	exec_single_left(t_infile *in)
{
	int	fd;

	if (access(in->file, F_OK) != 0)
		return (printf("BRUVA\n"), 1);
	fd = open(in->file, O_RDONLY);
	if (fd < 0)
		return (perror(in->file), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
	return (0);
}

int	exec_double_left(t_infile *in, t_cmds *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;
	// printf("DOUBLE LEFT\n");
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		get_single_heredoc(in->file, p);
		close(p[1]);
		children_killer(0);
	}
	else
	{
		double_helper(status, p, pid);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (close(p[0]), btree()->global_signal = 130, -1);
		in->heredoc_fd = p[0];
	}
	return (0);
}

int	exec_out_redirections(t_outfile *out)
{
	int	fd;
	int	flags;

	while (out)
	{
		flags = O_WRONLY | O_CREAT;
		if (ft_strcmp(out->token, ">") == 0)
			flags |= O_TRUNC;
		else if (ft_strcmp(out->token, ">>") == 0)
			flags |= O_APPEND;
		else
			return (fprintf(stderr, "Unknown redirection: %s\n", out->token),
				-1);
		fd = open(out->file, flags, 0644);
		if (fd < 0)
			return (perror(out->file), -1);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (perror("dup2"), close(fd), -1);
		close(fd);
		out = out->next;
	}
	return (0);
}

int	exec_redirections(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	if (cmd->cmd == NULL)
		cmd->flag_to_exec = 1;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0 && in->heredoc_fd > 0)
		{
			if (dup2(in->heredoc_fd, STDIN_FILENO) < 0)
				return (perror("dup2"), close(in->heredoc_fd), -1);
			close(in->heredoc_fd);
		}
		else if (ft_strcmp(in->token, "<") == 0)
		{
			if (exec_single_left(in) < 0)
				return (-1);
		}
		in = in->next;
	}
	if (exec_out_redirections(cmd->outfiles) < 0)
		return (btree()->cmds->flag_to_exec = 1, -1);
	return (0);
}
