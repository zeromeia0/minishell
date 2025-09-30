/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_duper_hiper_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/30 19:29:35 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	free_matrix(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_env_node(t_os_envs *env)
{
	if (!env)
		return ;
	free(env->linux_envs);
	free(env);
}

void	free_env_list(t_os_envs *head)
{
	t_os_envs	*temp;

	while (head)
	{
		temp = head->next;
		free_env_node(head);
		head = temp;
	}
}

void	clear_env_list(void)
{
	t_os_envs	**env_list;
	t_os_envs	*current;
	t_os_envs	*next;

	env_list = get_env_list();
	current = *env_list;
	while (current)
	{
		next = current->next;
		free(current->linux_envs);
		free(current->temp_vars);
		free(current);
		current = next;
	}
	*env_list = NULL;
}

void free_os_envs(void)
{
	
}
