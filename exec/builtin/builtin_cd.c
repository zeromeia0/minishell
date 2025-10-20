/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:17:21 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/20 10:49:22 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

char	*builtin_cd_aux(char **args)
{
	char	*target;

	if (!args[1] || args[1][0] == '\0')
	{
		target = find_path_in_list(*get_env_list(), "HOME=");
		if (!target)
			return (my_ffprintf(target, "cd: HOME not set\n"), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = find_path_in_list(*get_env_list(), "OLDPWD=");
		if (!target)
			return (my_ffprintf(target, "cd: OLDPWD not set\n"), NULL);
		printf("%s\n", target);
	}
	else if (args[2])
		return (my_ffprintf(args[0], "too many arguments\n"), NULL);
	else
		target = args[1];
	return (target);
}

static char	*pwd_updater(char *oldpwd, char *target)
{
	char	*newpwd;

	newpwd = logical_pwd_update(oldpwd, target);
	if (newpwd)
	{
		update_env_var("PWD=", newpwd);
		free(newpwd);
	}
	else
		ft_putstr_fd("cd: failed to update PWD\n", 2);
	return (newpwd);
}

int	builtin_cd(char **args)
{
	char	*oldpwd;
	char	buf[1024];
	char	*target;

	oldpwd = find_path_in_list(*get_env_list(), "PWD=");
	target = builtin_cd_aux(args);
	if (!target)
		return (1);
	if (chdir(target) != 0)
		return (perror("cd"), 1);
	if (oldpwd)
		update_env_var("OLDPWD=", oldpwd);
	if (getcwd(buf, sizeof(buf)) != NULL)
		update_env_var("PWD=", buf);
	else
		pwd_updater(oldpwd, target);
	return (0);
}
