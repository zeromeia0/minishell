/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:59 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 15:18:13 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

t_os_envs	**get_env_list(void)
{
	static t_os_envs	*env_list = NULL;

	return (&env_list);
}

t_os_envs	*create_env_node(char *path)
{
	t_os_envs	*new_node;

	new_node = malloc(sizeof(t_os_envs));
	if (!new_node)
		return (NULL);
	new_node->linux_envs = ft_strdup(path);
	if (!new_node->linux_envs)
		return (free(new_node), NULL);
	new_node->next = NULL;
	new_node->temp_vars = NULL;
	return (new_node);
}

void	enhanced_sorting_stoled_from_jlima(t_os_envs *envs)
{
	t_os_envs	*env2;

	while (envs)
	{
		env2 = envs->next;
		while (env2)
		{
			if (ft_abs_strcmp(envs->linux_envs, env2->linux_envs) > 0)
				ft_ult_swap(&envs->linux_envs, &env2->linux_envs);
			env2 = env2->next;
		}
		envs = envs->next;
	}
}

char	*add_quotes_export(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
	{
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!new_str)
			return (NULL);
		ft_strcpy(new_str, str);
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!new_str)
		return (NULL);
	new_str = helper_add_quotes_export(new_str, str);
	return (new_str);
}

void	export_print_env_list(void)
{
	t_os_envs	*current;
	char		*print_it;

	current = *get_env_list();
	while (current)
	{
		if (current->linux_envs)
		{
			print_it = add_quotes_export(current->linux_envs);
			printf("declare -x %s\n", print_it);
			free(print_it);
		}
		if (current->temp_vars)
		{
			print_it = add_quotes_export(current->temp_vars);
			printf("declare -x %s\n", print_it);
			free(print_it);
		}
		current = current->next;
	}
}
