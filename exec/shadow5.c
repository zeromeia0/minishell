/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 23:56:47 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/29 16:32:23 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	exec_child_helper(t_cmds *cmd, char **cleaned, char **updated_envs)
{
	int	checker;

	checker = 0;
	if (has_redir(cmd))
		exec_redirections(cmd, cleaned, updated_envs, 1);
	if (has_builtin(cmd))
		exec_builtin(cleaned[0], cleaned, updated_envs);
	else if (is_system_path_command(cleaned[0], updated_envs))
		exec_path(cleaned[0], cleaned, updated_envs);
	else if (super_checker_goated(cmd, cleaned, updated_envs) != 0)
		checker = 1;
	checker = 1;
	if (checker == 1 && !has_redir(cmd))
		my_ffprintf(cmd->cmd[0], "command not found\n");
	valgrind_destroyer(updated_envs, cleaned);
	megalodon_giga_chad_exit(127, 1);
}

int	check_paths(char **paths, char *cmd, int expected_access)
{
	int	i;
	int	access_result;

	if (!paths || !cmd)
		return (0);
	i = 0;
	while (paths[i])
	{
		access_result = check_path_access(paths[i], cmd);
		if (access_result == -1)
			return (-1);
		if (access_result == expected_access)
			return (1);
		i++;
	}
	return (0);
}

void	handle_wait_status(int status, int *exit_status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			btree()->global_signal = 130;
			btree()->exit_status = 130;
			*exit_status = 130;
		}
	}
	else if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
}

void	init_pwd_helper(void)
{
	char	*new_path;

	new_path = malloc(ft_strlen("PATH=/usr/local/sbin:/usr/local/bin:\
		/usr/sbin:/usr/bin:/sbin:/bin") + 1);
	if (!new_path)
		return ;
	ft_strcpy(new_path, "PATH=");
	ft_strcat(new_path,
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	add_new_env_var(get_env_list(), new_path);
	free(new_path);
}
