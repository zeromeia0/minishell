/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:44:52 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 09:38:30 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

int handle_non_slash_commands(char *cmd, char **args, char **envp)
{
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "command not found\n");
		exit(127);
	}
	else
	{
		if (access(cmd, X_OK) == 0)
		{
			prepare_for_exec();
			execve(cmd, args, envp);
			perror(cmd);
			exit (127);
		}
		else
			my_ffprintf(cmd, "Permission denied\n");
	}
	exit(126);
}

int	handle_absolute_path_cmd(char *cmd, char **args, char **envp)
{
	char	*new_args[3];
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
		{
			my_ffprintf(cmd, "No such file or directory\n");
			exit(127);
		}
		else
		{
			if (access(cmd, X_OK) == 0)
			{
				prepare_for_exec();
				execve(cmd, args, envp);
				if (errno == ENOEXEC)
				{
					new_args[0] = "/bin/bash";
					new_args[1] = cmd;
					new_args[2] = NULL;
					prepare_for_exec();
					execve(new_args[0], new_args, envp);
				}
				perror(cmd);
				exit (btree()->exit_status);
			}
			else
				my_ffprintf(cmd, "Permission denied\n"), exit(126);
		}
	}
	else
		handle_non_slash_commands(cmd, args, envp);
	return (0);
}

int	handle_system_path_cmd_aux(char *cmd, char **args, char **envp)
{
	char	*new_args[3];
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "No such file or directory\n");
		exit(126);
	}
	else
	{
		if (access(cmd, X_OK) == 0)
		{
			prepare_for_exec();
			execve(cmd, args, envp);
			if (errno == ENOEXEC)
			{
				new_args[0] = "/bin/bash";
				new_args[1] = cmd;
				new_args[2] = NULL;
				prepare_for_exec();
				execve(new_args[0], new_args, envp);
			}
			perror(cmd);
			exit(1);
		}
		else
		{
			my_ffprintf(cmd, "Permission denied\n");
			exit(126);
		}
	}
	return (0);
}

int	handle_system_path_cmd(char *cmd, char **args, char **envp)
{
	if (is_system_path_command(cmd, envp))
	{
		if (exec_system_path(cmd, args, envp) == 0)
			return (0);
	}
	else
	{
		if (handle_system_path_cmd_aux(cmd, args, envp) != 0)
			return (-1);
	}
	return (0);
}

int exec_path(char *cmd, char **args, char **envp)
{
    if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
        update_shell_level(1);
    if (strchr(cmd, '/'))
        return handle_absolute_path_cmd(cmd, args, envp);
    if (is_system_path_command(cmd, envp))
        return exec_system_path(cmd, args, envp);
    my_ffprintf(cmd, "command not found\n");
    exit (127);
}