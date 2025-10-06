/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_duper_hiper_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:02 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/06 15:30:42 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	free_matrix(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_env_node(t_os_envs *env)
{
	if (!env)
		return ;
	free(env->linux_envs);
	free(env);
}

void	free_env_list(t_os_envs *head)
{
	t_os_envs	*temp;

	while (head)
	{
		temp = head->next;
		free_env_node(head);
		head = temp;
	}
}

void	clear_env_list(void)
{
	t_os_envs	**env_list;
	t_os_envs	*current;
	t_os_envs	*next;

	env_list = get_env_list();
	current = *env_list;
	while (current)
	{
		next = current->next;
		free(current->linux_envs);
		free(current->temp_vars);
		free(current);
		current = next;
	}
	*env_list = NULL;
}

void free_os_envs(void)
{
    t_os_envs **env_list = get_env_list();
    t_os_envs *current = *env_list;
    t_os_envs *next;

    while (current)
    {
        next = current->next;
        free(current->linux_envs);
        free(current->temp_vars);
        free(current);
        current = next;
    }
    *env_list = NULL;
}

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

void	megalodon_giga_chad_exit(int status)
{
	printf("INSIDE MEGALODON\n");
	ft_free_matrix(btree()->env);
	free_os_envs();
	clear_env_list();
	close_all_non_standart_fds();
	binary_clear(btree());
	free(btree()->input);
	exit(status);
}

void	children_killer(int status)
{
	exit(status);
}


void	check_commands(char *cmd)
{
	if (btree()->cmds->flag_to_exec == 1)
		megalodon_giga_chad_exit(126);
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "No such file or directory\n");
		megalodon_giga_chad_exit(127);
	}
}

void	double_helper(int status, int p[2], pid_t pid)
{
	close(p[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	restart_signals();
}

int	check_cmds(t_cmds *cmds, char **args, char **envp)
{
	t_cmds	*current;

	if (!cmds || !cmds->cmd)
		return (1);
	current = cmds;
	while (current)
	{
		if (!is_cmd_valid(current, args, envp))
			return (0);
		current = current->next;
	}
	return (1);
}