/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:21:23 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/20 11:01:03 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else
		return (0);
}

int	has_builtin(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd)
		return (0);
	return (is_builtin(cmd->cmd[0]));
}

int	builtin_echo(char **args)
{
	int	i;
	int	suppress_newline;

	i = 1;
	suppress_newline = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		suppress_newline = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!suppress_newline)
		write(1, "\n", 1);
	return (0);
}

int	builtin_exit(char **args, char **envp)
{
	long	status;

	if (!args[1])
	{
		ft_free_matrix(envp);
		if (btree()->global_signal)
			status = btree()->global_signal;
		else
			status = btree()->exit_status;
		update_shell_level(-1);
		megalodon_giga_chad_exit((unsigned char)status, 1);
	}
	if (!is_numeric(args[1]))
		return (write(2, "exit\n", 6), my_ffprintf(args[0],
				"numeric argument required\n"), ft_free_matrix(envp),
			megalodon_giga_chad_exit(2, 1), 0);
	if (args[0] && args[1] && args[2] != NULL)
		return (ft_putstr_fd("minishell: exit: too many arguments", 2), 0);
	status = ft_atol(args[1]);
	update_shell_level(-1);
	return (ft_free_matrix(envp),
		megalodon_giga_chad_exit((unsigned char)status, 1), 0);
}

int	exec_builtin(char *cmd, char **args, char **envp)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd, "env") == 0)
		return (print_linux_env_list());
	else if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit(args, envp));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(args));
	else if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(args));
	return (1);
}
