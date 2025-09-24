/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:39:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 13:29:06 by vvazzs           ###   ########.fr       */
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



int	am_i_truly_myself(const char *cmd)
{
	char	*real;
	char	*self;
	int		result;

	real = my_realpath(cmd, NULL); //i think i can't use realpath
	self = my_realpath("/proc/self/exe", NULL); //tf is this
	result = real && self && strcmp(real, self) == 0;
	free(real);
	free(self);
	return (result);
}

void	my_ffprintf(char *cmd, char *which_message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, which_message, ft_strlen(which_message));
}
