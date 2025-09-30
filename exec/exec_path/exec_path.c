/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:44:52 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/30 22:16:18 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"
#include <string.h>
#include <unistd.h>

int	handle_non_slash_commands(char *cmd, char **args, char **envp)
{
	if (cmd == NULL)
		btree()->cmds->flag_to_exec = 1;
	if (btree()->cmds->flag_to_exec == 1)
		megalodon_giga_chad_exit(126);
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "command not found\n");
		megalodon_giga_chad_exit(127);
	}
	else
	{
		if (access(cmd, X_OK) == 0)
		{
			prepare_for_exec();
			execve(cmd, args, envp);
			perror(cmd);
			megalodon_giga_chad_exit(127);
		}
		else
			my_ffprintf(cmd, "Permission denied\n");
	}
	return (megalodon_giga_chad_exit(126), 0);
}

int	handle_slash_command(char *cmd, char **args, char **envp)
{
	if (cmd == NULL)
		btree()->cmds->flag_to_exec = 1;
	if (btree()->cmds->flag_to_exec == 1)
			megalodon_giga_chad_exit(126);
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "No such file or directory\n");
		megalodon_giga_chad_exit(127);
	}
	if (access(cmd, X_OK) == 0)
	{
		prepare_for_exec();
		execve(cmd, args, envp);
		if (errno == ENOEXEC)
		{
			buildup_new_args(cmd, envp);
			perror("/bin/bash");
			megalodon_giga_chad_exit(1);
		}
		perror(cmd);
		megalodon_giga_chad_exit(btree()->exit_status);
	}
	else
	{
		my_ffprintf(cmd, "Permission denied\n");
		megalodon_giga_chad_exit(126);
	}
	return (megalodon_giga_chad_exit(0), 0);
}

int	handle_system_path_cmd_aux(char *cmd, char **args, char **envp)
{
	if (cmd == NULL)
		btree()->cmds->flag_to_exec = 1;
	if (btree()->cmds->flag_to_exec == 1)
			megalodon_giga_chad_exit(126);
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "No such file or directory\n");
		megalodon_giga_chad_exit(126);
	}
	if (access(cmd, X_OK) == 0)
	{
		prepare_for_exec();
		execve(cmd, args, envp);
		if (errno == ENOEXEC)
		{
			buildup_new_args(cmd, envp);
			perror("/bin/bash");
			megalodon_giga_chad_exit(1);
		}
		perror(cmd);
		megalodon_giga_chad_exit(1);
	}
	else
	{
		my_ffprintf(cmd, "Permission denied\n");
		megalodon_giga_chad_exit(126);
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

int	exec_path(char *cmd, char **args, char **envp)
{
	if (am_i_truly_myself(args[0]) && access(cmd, F_OK) == 0 && access(cmd,
			X_OK) == 0)
		update_shell_level(1);
	if (strchr(cmd, '/'))
		return (handle_absolute_path_cmd(cmd, args, envp));
	if (is_system_path_command(cmd, envp))
		return (exec_system_path(cmd, args, envp));
	my_ffprintf(cmd, "command not found\n");
	return (megalodon_giga_chad_exit(127), 0);
}


	