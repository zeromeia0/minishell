/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:39:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/09 17:55:21 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

void	prepare_for_exec(void)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &btree()->orig_termios) == -1)
			perror("tcsetattr");
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*get_env_var(char *name, char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	am_i_truly_myself(const char *cmd)
{
	// printf("AM I MYSELF?\n");
	// if (stat(cmd, &btree()->cmd_stat) == -1)
	// 	return (0);
	// if (stat("/proc/self/exe", &btree()->self_stat) == -1)
	// 	return (0);
	return (btree()->cmd_stat.st_dev == btree()->self_stat.st_dev
		&& btree()->cmd_stat.st_ino == btree()->self_stat.st_ino);
}

void	my_ffprintf(char *cmd, char *which_message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, which_message, ft_strlen(which_message));
}
