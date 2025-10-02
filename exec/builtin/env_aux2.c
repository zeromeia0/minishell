/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:01:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/03 00:40:24 by namejojo         ###   ########.fr       */
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

char **expand_matrix(t_cmds *cmd)
{
	char	*temp;
	char	**holder;
	int		ind;
	int		len;
	int		flag;

	if (cmd->cmd == NULL)
		return (NULL);
	flag = 0;
	ind = -1;
	while (cmd->cmd[++ind])
	{
		if (ft_strchr(cmd->cmd[ind], '\n'))
		{
			holder = ft_split(cmd->cmd[ind], '\n');
			if (holder == NULL)
				return (btree()->type == ERROR, cmd->cmd);
			free(cmd->cmd[ind]);
			ft_matrix_uni(cmd->cmd + ind, cmd->cmd + ind + 1);
			len = ft_matlen(cmd->cmd);
			holder = ft_matrix_in_matrix(cmd->cmd, ind, holder);
			ind += ft_matlen(cmd->cmd) - len;
			cmd->expanded = cmd->expanded + (holder != cmd->cmd);
			if (flag)
				free(cmd->cmd);
			cmd->cmd = holder;
			flag = 1;
		}
	}
	return (cmd->cmd);
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
    expand_infiles(cmd->infiles);
    expand_outfiles(cmd->outfiles);
	cmd->cmd = expand_matrix(cmd);
	expand_args(cmd->next);
}

void	take_quotes(char *str)
{
	char	ch;
	int		ind;

	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			ind = 0;
			ch = str[ind];
			ind++;
			while (str[ind] != ch)
				ind++;
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
			ft_memmove(str, str + 1, ft_strlen(str));
			str += ind - 1;
		}
		else
			str++;
	}
}

void	expand_infiles(t_infile *infile)
{
	int		len;
	char	*temp;

	if (!infile || !infile->file)
		return ;
	if (ft_strcmp(infile->token, "<<"))
	{
		len = ft_strlen(infile->file);
		infile->flag = 0;
		take_quotes(infile->file);
		if (len != ft_strlen(infile->file))
			infile->flag = 1;
	}
	else
	{
		infile->file = quote(infile->file);
		if (ft_strchr(infile->file, '\n'))
		{
			temp = infile->file;
			infile->file = ft_strsubs(temp, '\n', ' ');
			free(temp);
		}
	}
	expand_infiles(infile->next);
}

void	expand_outfiles(t_outfile *outfile)
{
	char	*temp;

	if (!outfile || !outfile->file)
		return ;
	outfile->file = quote(outfile->file);
	if (ft_strchr(outfile->file, '\n'))
	{
		temp = outfile->file;
		outfile->file = ft_strsubs(temp, '\n', ' ');
		free(temp);
	}
	expand_outfiles(outfile->next);
}
