/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/08 09:11:29 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_child(t_cmds *cmd)
{
	char	**cleaned;
	char	**updated_envs;

	if (cmd && cmd->flag_to_exec == 1)
		return ;
	signal(SIGINT, handle_sigint);
	cleaned = array_to_exec(cmd);
	updated_envs = list_to_char(*get_env_list());
	if (has_redir(cmd))
		exec_redirections(cmd);
	if (has_builtin(cmd))
		exec_builtin(cleaned[0], cleaned, updated_envs);
	else
		exec_path(cleaned[0], cleaned, updated_envs);
	free_matrix(cleaned);
	free_matrix(updated_envs);
}


int	exec_single_cmd(t_cmds *cmd)
{
	if (!cmd || !cmd->cmd)
		return (btree()->exit_status);
	if (cmd->flag_to_exec == 1)
		return (btree()->exit_status);
	if (has_builtin(cmd) && !has_redir(cmd))
		return (exec_single_cmd_aux(cmd));
	prepare_signals_and_fork(cmd);
	return (btree()->exit_status); // GOTTA FIX THIS SHIT
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

int check_order(t_binary *tree, char **args, char **envp)
{
    if (!tree)
        return (0);

    if (handle_heredoc(tree->cmds) < 0)
    {
        if (tree->cmds)
            tree->cmds->flag_to_exec = 1;
        return (-1);
    }
    if (!check_infiles(tree->cmds))
        return (0);
    if (!check_outfiles(tree->cmds))
        return (0);
    if (!check_cmds(tree->cmds, args, envp))
        return (0);
    return (1);
}


int exec_tree(t_binary *tree, char **args, char **envp)
{
    int ret_left;
    int co;

    if (!tree)
        return ( 0);
    if (tree->cmds && tree->cmds->flag_to_exec == 1)
        return (1);
    co = check_order(tree, args, envp);
    if (co < 0)
        return (btree()->global_signal == 130 ? 130 : 1);
    if (co == 0)
        return (1);
    if (btree()->global_signal == 130)
        return (130);
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

