/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:47:26 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 21:04:11 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	check_var_match(t_os_envs *cur, char *var_name, size_t name_len)
{
	if (cur->linux_envs && ft_strncmp(cur->linux_envs, var_name, name_len) == 0
		&& cur->linux_envs[name_len] == '=')
		return (1);
	if (cur->temp_vars && ft_strncmp(cur->temp_vars, var_name, name_len) == 0)
		return (1);
	return (0);
}

void	remove_env_node(t_os_envs **env_list, t_os_envs *prev,
		t_os_envs *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		*env_list = cur->next;
	free(cur->linux_envs);
	free(cur->temp_vars);
	free(cur);
}

int	unset_env_var(t_os_envs **env_list, char *var_name, size_t name_len)
{
	t_os_envs	*cur;
	t_os_envs	*prev;

	prev = NULL;
	cur = *env_list;
	while (cur)
	{
		if (check_var_match(cur, var_name, name_len))
		{
			remove_env_node(env_list, prev, cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	builtin_unset(char **args)
{
	int			i;
	size_t		name_len;
	t_os_envs	**env_list;

	if (!args[1])
		return (-1);
	env_list = get_env_list();
	i = 1;
	while (args[i])
	{
		name_len = strlen(args[i]);
		unset_env_var(env_list, args[i], name_len);
		i++;
	}
	return (0);
}

void	sig_handle_heredoc_more(int sig)
{
	(void)sig;
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	btree()->global_signal = 130;
	btree()->exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	megalodon_giga_chad_exit(130, 1);
}
