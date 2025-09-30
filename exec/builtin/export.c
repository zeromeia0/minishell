/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 23:57:32 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 22:05:13 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	update_existing_env_var(t_os_envs *current, const char *str,
		size_t len)
{
	char	*new_var;

	if (current->linux_envs && ft_strncmp(current->linux_envs, str, len) == 0)
	{
		if (current->linux_envs[len] == '=' || current->linux_envs[len] == '\0')
		{
			new_var = ft_strdup(str);
			if (!new_var)
				return (-1);
			free(current->linux_envs);
			current->linux_envs = new_var;
			if (current->temp_vars)
			{
				free(current->temp_vars);
				current->temp_vars = NULL;
			}
			return (0);
		}
	}
	return (1);
}

int	convert_temp_to_env_var(t_os_envs *current, const char *str,
		size_t len)
{
	char	*new_var;

	if (current->temp_vars && ft_strncmp(current->temp_vars, str, len) == 0
		&& current->temp_vars[len] == '\0')
	{
		new_var = ft_strdup(str);
		if (!new_var)
			return (-1);
		free(current->temp_vars);
		current->temp_vars = NULL;
		if (current->linux_envs)
			free(current->linux_envs);
		current->linux_envs = new_var;
		return (0);
	}
	return (1);
}

int	make_update_env_aux(t_os_envs **env_list, const char *str,
		size_t len)
{
	t_os_envs	*current;
	int			result;

	current = *env_list;
	while (current)
	{
		result = update_existing_env_var(current, str, len);
		if (result == 0)
			return (0);
		if (result == -1)
			return (-1);
		result = convert_temp_to_env_var(current, str, len);
		if (result == 0)
			return (0);
		if (result == -1)
			return (-1);
		current = current->next;
	}
	return (1);
}

size_t	get_env_key_length(const char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		return ((size_t)(equal_sign - str));
	else
		return (strlen(str));
}

int	builtin_export(char **args)
{
	int		i;
	size_t	len;

	i = 1;
	if (!args[1])
		return (export_print_env_list(), 0);
	while (args[i])
	{
		len = get_env_key_length(args[i]);
		if (make_update_env(args[i]) == 1)
		{
			if (!strchr(args[i], '='))
				add_temp_var(args[i]);
			else if (add_new_env_var(get_env_list(), args[i]) < 0)
				return (perror("minishell: export"), 1);
		}
		i++;
	}
	return (0);
}
