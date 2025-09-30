/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:22:49 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/29 21:41:46 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

void	buildup_new_args(char *cmd, char **envp)
{
	char	*new_args[3];

	new_args[0] = "/bin/bash";
	new_args[1] = cmd;
	new_args[2] = NULL;
	prepare_for_exec();
		// printf("faz parte 2\n");

	execve(new_args[0], new_args, envp);
}

int	handle_absolute_path_cmd(char *cmd, char **args, char **envp)
{
	if (strchr(cmd, '/'))
		return (handle_slash_command(cmd, args, envp));
	else
		handle_non_slash_commands(cmd, args, envp);
	return (0);
}
