/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:17:50 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 22:47:28 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	child_services(char **cleaned_cmd, char **envp, int status)
{
	if (ft_strcmp(cleaned_cmd[0], "exit") == 0)
		status = pipes_builtin_exit(cleaned_cmd, envp);
	status = exec_builtin(cleaned_cmd[0], cleaned_cmd, envp);
	ft_free_matrix(cleaned_cmd);
	ft_free_matrix(envp);
	megalodon_giga_chad_exit(status, 0);
}

void	file_descriptor_closer(int fd[2])
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

int	get_heredoc_fd(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (in->token && ft_strcmp(in->token, "<<") == 0)
			return (in->heredoc_fd);
		in = in->next;
	}
	return (-1);
}

int	has_heredocs(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			return (1);
		in = in->next;
	}
	return (0);
}

int	pipes_builtin_exit(char **args, char **envp)
{
	long	status;

	if (!args[1])
	{
		ft_free_matrix(envp);
		ft_free_matrix(args);
		if (btree()->global_signal)
			status = btree()->global_signal;
		else
			status = btree()->exit_status;
		update_shell_level(-1);
		megalodon_giga_chad_exit((unsigned char)status, 0);
	}
	if (!is_numeric(args[1]))
		return (my_ffprintf(args[1], "numeric argument required"), 0);
	if (args[0] && args[1] && args[2] != NULL)
		return (ft_putstr_fd("minishell: exit: too many arguments", 2), 0);
	status = ft_atol(args[1]);
	update_shell_level(-1);
	return (ft_free_matrix(envp), ft_free_matrix(args),
		megalodon_giga_chad_exit((unsigned char)status, 0), 0);
}
