/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 23:57:32 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 22:39:55 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	update_existing_env_var(t_os_envs *current, const char *str, size_t len)
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

int	convert_temp_to_env_var(t_os_envs *current, const char *str, size_t len)
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

int	make_update_env_aux(t_os_envs **env_list, const char *str, size_t len)
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

t_os_envs	*find_env_var(t_os_envs *env_list, const char *arg)
{
	int		len;
	char	*symbol;
	char	*env_eq;
	int		env_len;

	symbol = ft_strchr(arg, '=');
	len = (symbol) ? (symbol - arg) : (int)ft_strlen(arg);
	while (env_list)
	{
		if (env_list->linux_envs)
		{
			env_eq = ft_strchr(env_list->linux_envs, '=');
			env_len = (env_eq) ? (env_eq
					- env_list->linux_envs) : (int)ft_strlen(env_list->linux_envs);
			if (env_len == len && ft_strncmp(env_list->linux_envs, arg,
					len) == 0)
				return (env_list);
		}
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

int	builtin_export(char **args)
{
	int	i;
	int	check;

	i = 1;
	if (!args[1])
		return (export_print_env_list(), 0);
	while (args[i])
	{
		check = export_args_checker(args, i);
		if (check == -1)
		{
			i++;
			continue ;
		}
		else if (check == 1)
		{
			if (!find_env_var(*get_env_list(), args[i]))
				add_temp_var(args[i]);
			i += 2;
			continue ;
		}
		else if (check == 2)
		{
			if (make_update_env(args[i]) != 0)
			{
				if (add_new_env_var(get_env_list(), args[i]) < 0)
					return (perror("minishell: export"), 1);
			}
			i += 2;
			continue ;
		}
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
		i++;
	}
	return (0);
}
