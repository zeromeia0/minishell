/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overall_builtin_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 23:53:03 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/20 13:50:34 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

void	update_env_var(const char *key, const char *value)
{
	char	*arg;
	char	*args[3];

	arg = malloc(strlen(key) + strlen(value) + 1);
	if (!arg)
		return ;
	strcpy(arg, key);
	strcat(arg, value);
	args[0] = "export";
	args[1] = arg;
	args[2] = NULL;
	builtin_export(args);
	free(arg);
}

char	*join_paths(const char *oldpwd, const char *target)
{
	char	*newpwd;
	size_t	len;

	len = strlen(oldpwd) + 1 + strlen(target) + 1;
	newpwd = malloc(len);
	if (!newpwd)
		return (NULL);
	ft_strcpy(newpwd, (char *)oldpwd);
	ft_strcat(newpwd, "/");
	ft_strcat(newpwd, (char *)target);
	return (newpwd);
}

char	*logical_pwd_update(const char *oldpwd, const char *target)
{
	char	*newpwd;
	char	*slash;

	if (!oldpwd)
		return (NULL);
	if (ft_strcmp(target, "..") == 0)
	{
		newpwd = ft_strdup(oldpwd);
		if (!newpwd)
			return (NULL);
		slash = ft_strrchr(newpwd, '/');
		if (slash && slash != newpwd)
			*slash = '\0';
		else
			*(slash + 1) = '\0';
		return (newpwd);
	}
	else if (ft_strcmp(target, ".") == 0)
		return (ft_strdup(oldpwd));
	else if (target[0] == '/')
		return (ft_strdup(target));
	else
		return (join_paths(oldpwd, target));
}
