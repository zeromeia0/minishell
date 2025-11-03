/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:22:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/03 14:38:02 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;
	char	buf[1024];

	pwd = find_path_in_list(*get_env_list(), "PWD=");
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		if (getcwd(buf, sizeof(buf)) != NULL)
			printf("%s\n", buf);
		else
			return (perror("pwd"), 0);
	}
	return (0);
}

bool	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	deal_with_bad_exit(t_cmds *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0 && cmd->cmd[1]
		&& !is_numeric(cmd->cmd[1]))
	{
		btree()->exit_status = 2;
		return (write(2, "exit\n", 6), my_ffprintf(cmd->cmd[1],
				"numeric argument required\n"), megalodon_giga_chad_exit(2, 0),
			1);
	}
	if ((ft_strcmp(cmd->cmd[0], "exit") == 0) && cmd->cmd[1] && cmd->cmd[2])
	{
		btree()->exit_status = 2;
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

int	exec_single_cmd_aux(t_cmds *cmd)
{
	int		status;
	char	**env_array;

	if (deal_with_bad_exit(cmd) != 1)
		return (btree()->exit_status);
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
	{
		env_array = list_to_char(*get_env_list());
		status = exec_builtin(cmd->cmd[0], cmd->cmd, env_array);
		free_matrix(env_array);
	}
	else
		status = exec_builtin(cmd->cmd[0], cmd->cmd, NULL);
	return (status);
}
