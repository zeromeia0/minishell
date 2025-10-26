/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:36:54 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 23:10:24 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

char	*find_path(char **envp, char *which_env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], which_env, (ft_strlen(which_env))) == 0)
			return (ft_strdup(envp[i] + ft_strlen(which_env)));
		i++;
	}
	return (NULL);
}

char	**split_path(char **envp)
{
	char	*path;
	char	**vars;

	path = find_path(envp, "PATH=");
	if (!path)
		return (NULL);
	vars = ft_split(path, ':');
	free(path);
	return (vars);
}

char	**get_paths_to_search(char **envp)
{
	return (split_path(envp));
}

int	check_path_access(char *path, char *cmd)
{
	int		result;
	char	*full_path;

	full_path = malloc(strlen(path) + strlen(cmd) + 2);
	if (!full_path)
	{
		perror("malloc failed");
		return (-1);
	}
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	result = (access(full_path, X_OK) == 0);
	free(full_path);
	return (result);
}

static int	check_paths(char **paths, char *cmd, int expected_access)
{
	int	i;
	int	access_result;

	if (!paths || !cmd)
		return (0);
	for (i = 0; paths[i]; i++)
	{
		access_result = check_path_access(paths[i], cmd);
		if (access_result == -1)
			return (-1);
		if (access_result == expected_access)
			return (1);
	}
	return (0);
}

int	is_system_path_command(char *cmd, char **envp)
{
	char	**paths_to_search;
	int		result;

	if (!cmd)
		return (0);
	paths_to_search = get_paths_to_search(envp);
	if (!paths_to_search)
		return (-1);
	if (ft_strchr(cmd, '/'))
		result = check_paths(paths_to_search, cmd, 0);
	else
		result = check_paths(paths_to_search, cmd, 1);
	ft_free_matrix(paths_to_search);
	return (result);
}
