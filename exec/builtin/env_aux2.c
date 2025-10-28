/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:01:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/28 17:49:49 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	print_linux_env_list(void)
{
	t_os_envs	*current;

	current = *get_env_list();
	while (current)
	{
		if (current->linux_envs)
			printf("%s\n", current->linux_envs);
		current = current->next;
	}
	return (1);
}

void	initialize_pwd(char **envp)
{
	char	buf[1024];
	char	*pwd_value;
	char	*full;
	char	*path_value;

	pwd_value = find_path(envp, "PWD=");
	if (!pwd_value)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
			return (perror("getcwd"));
		full = malloc(strlen("PWD=") + strlen(buf) + 1);
		if (!full)
			return ;
		ft_strcpy(full, "PWD=");
		ft_strcat(full, buf);
		add_new_env_var(get_env_list(), full);
		free(full);
	}
	path_value = find_path(envp, "PATH=");
	if (!path_value)
		init_pwd_helper();
	else
		free(pwd_value);
	free(path_value);
}

char	*find_temp_var(const char *key)
{
	t_os_envs	*env;
	size_t		len;

	env = *get_env_list();
	len = strlen(key);
	while (env)
	{
		if (env->temp_vars && ft_strncmp(env->temp_vars, key, len) == 0
			&& env->temp_vars[len] == '=')
			return (env->temp_vars + len + 1);
		env = env->next;
	}
	return (NULL);
}

void	free_asterisc(char **mat)
{
	int	ind;

	ind = -1;
	while (mat && mat[++ind])
	{
		if (ft_strchr(mat[ind], '*'))
			free(mat[ind]);
	}
}

char	**expand_matrix(t_cmds *cmd, int flag, int ind)
{
	char	**holder;

	if (cmd->cmd == NULL)
		return (NULL);
	while (cmd->cmd[++ind])
	{
		if (ft_strchr(cmd->cmd[ind], ' ') || ft_strchr(cmd->cmd[ind], '\n'))
		{
			holder = ft_split_sep(cmd->cmd[ind], ' ', '\n');
			if (holder == NULL)
				return (btree()->type = ERROR, cmd->cmd);
			free(cmd->cmd[ind]);
			ft_matrix_uni(cmd->cmd + ind, cmd->cmd + ind + 1);
			holder = ft_matrix_in_matrix(cmd->cmd, ind, holder);
			cmd->expanded = cmd->expanded + (holder != cmd->cmd);
			if (flag)
				free(cmd->cmd);
			cmd->cmd = holder;
			flag = 1;
		}
	}
	return (cmd->cmd);
}
