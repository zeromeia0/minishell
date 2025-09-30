/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:02:46 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 22:05:25 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	add_new_env_var(t_os_envs **env_list, const char *str)
{
	t_os_envs	*new_node;
	t_os_envs	*current;

	new_node = malloc(sizeof(t_os_envs));
	if (!new_node)
		return (-1);
	new_node->linux_envs = ft_strdup(str);
	if (!new_node->linux_envs)
		return (free(new_node), -1);
	new_node->temp_vars = NULL;
	new_node->next = NULL;
	if (!*env_list)
	{
		*env_list = new_node;
	}
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

int	make_update_env(const char *str)
{
	t_os_envs	**env_list;
	size_t		len;
	int			result;

	env_list = get_env_list();
	len = get_env_key_length(str);
	result = make_update_env_aux(env_list, str, len);
	if (result == 0)
		return (0);
	if (result == -1)
		return (-1);
	return (add_new_env_var(env_list, str));
}
