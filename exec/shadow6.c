/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:05:04 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 23:09:12 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

t_os_envs	*find_env_var(t_os_envs *env_list, const char *arg)
{
	while (env_list)
	{
		if (find_helper(env_list->linux_envs, arg))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	print_invalid_export(char *token)
{
	write(2, "export: ", 8);
	my_ffprintf(token, "not a valid identifier\n");
}

int	export_args_checker(char **args, int i)
{
	char	*arg;

	arg = args[i];
	if (!arg)
		return (-1);
	if (arg[0] == '=')
		return (print_invalid_export(arg), -1);
	if (args[i + 1] && args[i + 1][0] == '=')
		return (print_invalid_export(args[i + 1]), 1);
	if (ft_strchr(arg, '=') && arg[ft_strlen(arg) - 1] == '=' && args[i + 1])
		return (print_invalid_export(args[i + 1]), 2);
	return (0);
}

int	handle_valid_export(char **args, int i)
{
	if (ft_strchr(args[i], '='))
	{
		if (make_update_env(args[i]) != 0)
		{
			if (add_new_env_var(get_env_list(), args[i]) < 0)
				return (perror("minishell: export"), 1);
		}
	}
	else if (!find_env_var(*get_env_list(), args[i]))
		add_temp_var(args[i]);
	return (0);
}

int	process_export_arg(char **args, int i)
{
	int	check;

	check = export_args_checker(args, i);
	if (check == -1)
		return (i + 1);
	else if (check == 1)
	{
		if (!find_env_var(*get_env_list(), args[i]))
			add_temp_var(args[i]);
		return (i + 2);
	}
	else if (check == 2)
	{
		if (make_update_env(args[i]) != 0)
		{
			if (add_new_env_var(get_env_list(), args[i]) < 0)
				return (perror("minishell: export"), -1);
		}
		return (i + 2);
	}
	if (handle_valid_export(args, i) != 0)
		return (-1);
	return (i + 1);
}
