/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:24:11 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/09 15:46:20 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	count_it(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	write_dolar_home(char **envp)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	if (!envp || !*envp)
		write(2, "NO environment variables\n", 26);
	while (envp[i])
	{
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
		{
			home = ft_strdup(envp[i] + 5);
			my_ffprintf(home, "Is a directory\n");
			free(home);
		}
		i++;
	}
	free_matrix(envp);
}
