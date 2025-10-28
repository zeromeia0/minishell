/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:17:50 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 21:55:13 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_all_non_standart_fds(void)
{
	int	fd;

	fd = 2;
	while (++fd <= FOPEN_MAX)
		ft_close(fd);
}

void	megalodon_giga_chad_exit(int status, int flag)
{
	if (btree())
	{
		if (flag == 1)
			ft_free_matrix(btree()->env);
		free_os_envs();
		clear_env_list();
		close_all_non_standart_fds();
		binary_clear(btree());
		free(btree()->input);
	}
	exit(status);
}

void	children_killer(int status)
{
	exit(status);
}

void	check_commands(char **cmd, char **envp)
{
	if (btree()->cmds->flag_to_exec == 1)
		megalodon_giga_chad_exit(126, 0);
	if (access(cmd[0], F_OK) != 0)
	{
		my_ffprintf(cmd[0], "No such file or directory\n");
		ft_free_matrix(cmd);
		ft_free_matrix(envp);
		megalodon_giga_chad_exit(127, 1);
	}
}
