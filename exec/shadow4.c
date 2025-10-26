/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:20:04 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 22:17:46 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "minishell.h"

void	reset_heredoc_flags(t_binary *tree)
{
	t_cmds	*cmd;

	if (!tree)
		return ;
	cmd = tree->cmds;
	while (cmd)
	{
		cmd->heredoc_done = 0;
		cmd = cmd->next;
	}
	reset_heredoc_flags(tree->left);
	reset_heredoc_flags(tree->right);
}

void	help_to_process(t_cmds *cmd, int p[2])
{
	close(p[0]);
	printf("pipes\n");
	signal(SIGINT, sig_handle_heredoc);
	process_all_heredocs(cmd->infiles, p);
	close(p[1]);
	megalodon_giga_chad_exit(0, 0);
}

int	handle_single_heredoc_stuff(t_infile *in)
{
	int		fd[2];
	pid_t	pid;
	printf("heredoc stuff\n");
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		get_single_heredoc(in->file, fd);
		megalodon_giga_chad_exit(0, 0);
	}
	else
	{
		close(fd[1]);
		in->heredoc_fd = fd[0];
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	exec_empty_heredoc_node(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
		{
			if (handle_single_heredoc_stuff(in) == -1)
				return (-1);
		}
		in = in->next;
	}
	if (btree()->env)
		ft_free_matrix(btree()->env);
	return (0);
}

void	execute_child_helper(char **cleaned_cmd, char **env, t_cmds *cmd)
{
	int			status;
	t_infile	*in;

	status = 0;
	if (!cleaned_cmd || !cleaned_cmd[0])
	{
		ft_free_matrix(cleaned_cmd);
		in = cmd->infiles;
		while (in)
		{
			if (ft_strcmp(in->token, "<<") == 0 && cmd->heredoc_done == 0)
				if (exec_empty_heredoc_node(cmd) != 0)
					megalodon_giga_chad_exit(1, 1);
			in = in->next;
		}
		megalodon_giga_chad_exit(0, 1);
	}
	if (is_builtin(cleaned_cmd[0]))
		child_services(cleaned_cmd, env, status);
	else
	{
		exec_path(cleaned_cmd[0], cleaned_cmd, env);
		ft_free_matrix(cleaned_cmd);
		megalodon_giga_chad_exit(127, 1);
	}
}
