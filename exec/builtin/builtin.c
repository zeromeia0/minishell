/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:21:23 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 15:24:49 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else
		return (0);
}

int	has_builtin(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
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

int is_numeric(const char *s)
{
    int i = 0;
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


int builtin_exit(char **args, char **envp)
{
    long status;

    (void)envp;
    if (!args[1])
    {
        if (btree()->global_signal)
            status = btree()->global_signal;
        else
            status = btree()->exit_status;
        update_shell_level(-1);
        exit((unsigned char)status);
    }
    if (!is_numeric(args[1]))
		return (my_ffprintf(args[1], "numeric argument required"), 0);
    if (args[2])
        return (ft_putstr_fd("minishell: exit: too many arguments", 2), 1);
    status = ft_atol(args[1]);
    update_shell_level(-1);
    exit((unsigned char)status);
}

int	exec_builtin(char *cmd, char **args, char **envp)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (builtin_cd(args));
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (print_linux_env_list());
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (builtin_echo(args));
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (builtin_exit(args, envp));
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (builtin_unset(args));
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (builtin_export(args));
	return (1);
}
