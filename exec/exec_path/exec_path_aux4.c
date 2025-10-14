/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:22:49 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/13 16:38:55 by vivaz-ca         ###   ########.fr       */
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
	execve(new_args[0], new_args, envp);
}

int	handle_absolute_path_cmd(char *cmd, char **args, char **envp)
{
	if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd,
			X_OK) == 0)
		update_shell_level(1);
	if (strchr(cmd, '/'))
		return (handle_slash_command(cmd, args, envp));
	else
		handle_non_slash_commands(cmd, args, envp);
	return (0);
}
