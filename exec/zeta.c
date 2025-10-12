/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:40:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/12 21:41:52 by vvazzs           ###   ########.fr       */
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