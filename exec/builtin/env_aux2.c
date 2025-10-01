/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:01:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/01 10:39:36 by namejojo         ###   ########.fr       */
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

	pwd_value = find_path(envp, "PWD=");
	if (!pwd_value)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			perror("getcwd");
			return ;
		}
		full = malloc(strlen("PWD=") + strlen(buf) + 1);
		if (!full)
			return ;
		ft_strcpy(full, "PWD=");
		ft_strcat(full, buf);
		add_new_env_var(get_env_list(), full);
		free(full);
	}
	else
		free(pwd_value);
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

void	expand_args(t_cmds *cmd)
{
	char	**mat;
	char	**temp;
	int		ind;

	if (!cmd)
		return ;
	temp = cmd->cmd;
	mat = wildcards(temp, 0, 0);
	cmd->expanded = (temp != mat);
	if (temp != mat)
		free_matrix_nodes(temp);
	else
	{
		ind = -1;
		while (mat[++ind])
			mat[ind] = quote(mat[ind]);
	}
	cmd->cmd = mat;
	while (cmd->cmd && *cmd->cmd && **cmd->cmd == '\0')
	{
		fflush(stdout);
		free(*cmd->cmd);
		ft_matrix_uni(cmd->cmd, cmd->cmd + 1);
	}
    expand_infiles(cmd->infiles);
    expand_outfiles(cmd->outfiles);
	expand_args(cmd->next);
}

void	expand_infiles(t_infile *infile)
{
	if (!infile || !infile->file)
		return ;
	infile->file = expand_hd(infile->file);
	expand_infiles(infile->next);
}

void	expand_outfiles(t_outfile *outfile)
{
	if (!outfile || !outfile->file)
		return ;
	outfile->file = expand_hd(outfile->file);
	expand_outfiles(outfile->next);
}
