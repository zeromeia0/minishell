/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:08:05 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 23:14:09 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
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
			new_argv[j++] = ft_strdup(cmd->cmd[i++]);
	}
	new_argv[j] = NULL;
	return (new_argv);
}

int	exec_single_left(t_infile *in, char **envp, char **cleaned)
{
	int	fd;

	if (access(in->file, F_OK) != 0)
	{
		perror(in->file);
		if (btree()->cmds->export_flag == 1)
			return (ft_free_matrix(cleaned), ft_free_matrix(envp),
				megalodon_giga_chad_exit(0, 1), -1);
		else
			return (ft_free_matrix(cleaned), ft_free_matrix(envp),
				megalodon_giga_chad_exit(0, 0), -1);
	}
	fd = open(in->file, O_RDONLY);
	if (fd < 0)
		return (perror(in->file), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
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
			return (ft_putstr_fd("Unknown redirection: ", STDERR_FILENO),
				ft_putstr_fd(out->token, STDERR_FILENO), ft_putstr_fd("\n",
					STDERR_FILENO), -1);
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

int	exec_input_redirections(t_infile *in, int *last_heredoc_fd,
		char **envp, char **cleaned)
{
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0 && in->heredoc_fd >= 0)
		{
			if (*last_heredoc_fd >= 0)
				close(*last_heredoc_fd);
			*last_heredoc_fd = in->heredoc_fd;
		}
		else if (ft_strcmp(in->token, "<") == 0)
		{
			if (exec_single_left(in, envp, cleaned) < 0)
				return (-1);
		}
		in = in->next;
	}
	return (0);
}

int	exec_redirections(t_cmds *cmd, char **envp, char **cleaned, int flag)
{
	int	last_heredoc_fd;

	last_heredoc_fd = -1;
	cmd->export_flag = flag;
	if (exec_input_redirections(cmd->infiles, &last_heredoc_fd, envp,
			cleaned) < 0)
		return (-1);
	if (last_heredoc_fd >= 0)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), close(last_heredoc_fd), -1);
		close(last_heredoc_fd);
	}
	if (exec_out_redirections(cmd->outfiles) < 0)
	{
		btree()->cmds->flag_to_exec = 1;
		return (-1);
	}
	return (0);
}
