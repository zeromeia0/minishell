/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:41:23 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/01 12:02:39 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	exec_system_path_aux1(char **envp, char ***paths_to_search)
{
	*paths_to_search = split_path(envp);
	if (!*paths_to_search)
	{
		write(2, "PATH not found\n", 15);
		megalodon_giga_chad_exit(0);
	}
	return (0);
}

int	exec_system_path_aux_aux(char *full_path, char **args, char **envp)
{
	if (access(full_path, X_OK) == 0)
	{
		prepare_for_exec();
		execve(full_path, args, envp);
		perror("execve failed");
		return (-1);
	}
	else
		return (perror("permission denied"), -1);
}

int	exec_system_path_aux2(char *cmd, char **args, char **envp,
		char **paths_to_search)
{
	int		i;
	char	*full_path;
	int		result;

	i = 0;
	while (paths_to_search[i])
	{
		full_path = malloc(strlen(paths_to_search[i]) + strlen(cmd) + 2);
		if (!full_path)
			return (perror("malloc failed"), -1);
		strcpy(full_path, paths_to_search[i]);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			result = exec_system_path_aux_aux(full_path, args, envp);
			free(full_path);
			return (result);
		}
		free(full_path);
		i++;
	}
	return (-1);
}

int	exec_system_path(char *cmd, char **args, char **envp)
{
	int		i;
	int		result;
	char	**paths_to_search;

	if (ft_strchr(cmd, '/') == NULL)
	{
		if (exec_system_path_aux1(envp, &paths_to_search) != 0)
			return (-1);
	}
	result = exec_system_path_aux2(cmd, args, envp, paths_to_search);
	i = 0;
	while (paths_to_search[i])
		free(paths_to_search[i++]);
	free(paths_to_search);
	return (result);
}
