/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:39:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 14:38:19 by vvazzs           ###   ########.fr       */
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
} //explain why I need this function

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

int am_i_truly_myself(const char *cmd)
{
    struct stat cmd_stat, self_stat;
    
    if (stat(cmd, &cmd_stat) == -1)
        return (0);
    if (stat("/proc/self/exe", &self_stat) == -1)
        return (0);
    return (cmd_stat.st_dev == self_stat.st_dev && 
            cmd_stat.st_ino == self_stat.st_ino);
}

void	my_ffprintf(char *cmd, char *which_message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, which_message, ft_strlen(which_message));
}
