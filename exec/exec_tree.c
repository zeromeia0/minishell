/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/03 14:42:43 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_child(t_cmds *cmd)
{
	char	**cleaned;
	char	**updated_envs;

	if (!cmd || !cmd->cmd[0])
		megalodon_giga_chad_exit(0, 1);
	if (cmd && cmd->flag_to_exec == 1)
		megalodon_giga_chad_exit(btree()->exit_status, 0);
	signal(SIGINT, handle_sigint);
	cleaned = array_to_exec(cmd);
	updated_envs = list_to_char(*get_env_list());
	exec_child_helper(cmd, cleaned, updated_envs);
}

int	exec_node(t_binary *node, char **args, char **envp)
{
	if (!node)
		return (0);
	if (node->cmds != NULL)
	{
		expand_args(node->cmds);
		if (node->cmds->next)
			return (exec_pipes(node->cmds, btree()->env));
		else
			return (exec_single_cmd(node->cmds));
	}
	if (node->subshell != NULL)
		return (exec_subshell(node->subshell, args, envp));
	return (0);
}

int	check_order(t_binary *tree, char **args, char **envp)
{
	int	please;

	please = 0;
	if (!tree)
		return (1);
	if (tree->cmds)
	{
		if (check_helper(tree->cmds, &please) == -1)
			return (-1);
	}
	check_order(tree->left, args, envp);
	check_order(tree->right, args, envp);
	please = 0;
	return (1);
}

int	handle_logic_operations(t_binary *tree, char **args, char **envp)
{
	int	ret_left;

	if (tree->logic && ft_strcmp(tree->logic, "&&") == 0)
	{
		ret_left = exec_tree(tree->left, args, envp);
		if (ret_left == 0)
			return (exec_tree(tree->right, args, envp));
		return (ret_left);
	}
	if (tree->logic && ft_strcmp(tree->logic, "||") == 0)
	{
		ret_left = exec_tree(tree->left, args, envp);
		if (ret_left != 0)
			return (exec_tree(tree->right, args, envp));
		return (ret_left);
	}
	return (exec_node(tree, args, envp));
}

int	exec_tree(t_binary *tree, char **args, char **envp)
{
	int	co;
	int	signal_status;

	if (!tree)
		return (0);
	co = check_order(tree, args, envp);
	if (co < 0)
	{
		signal_status = btree()->global_signal;
		if (signal_status == 130)
			return (130);
		else
			return (1);
	}
	if (tree->cmds && tree->cmds->flag_to_exec == 1)
		return (1);
	if (btree()->global_signal == 130)
		return (130);
	return (handle_logic_operations(tree, args, envp));
}
