/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/11 21:53:17 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int super_checker_goated(t_cmds *cmd, char *command, char **args)
{
	if (!has_builtin(cmd) && !has_redir(cmd) && !is_system_path_command(cmd->cmd[0], args))
	{
		if (strchr(cmd->cmd[0], '/'))
			handle_absolute_path_cmd(cmd->cmd[0], args, args);
		return (1);
	}
	return (0);
}
void	exec_child(t_cmds *cmd)	
{
	char	**cleaned;
	char	**updated_envs;

	if (cmd && cmd->flag_to_exec == 1)
		megalodon_giga_chad_exit(btree()->exit_status, 0);
	signal(SIGINT, handle_sigint);
	cleaned = array_to_exec(cmd);
	updated_envs = list_to_char(*get_env_list());

	if (has_redir(cmd))
		exec_redirections(cmd);

	if (has_builtin(cmd))
		exec_builtin(cleaned[0], cleaned, updated_envs);
		
	if (is_system_path_command(cleaned[0], updated_envs))
		exec_path(cleaned[0], cleaned, updated_envs);
		
	if (super_checker_goated(cmd, cleaned[0], updated_envs) != 0)
		my_ffprintf(cmd->cmd[0], "command not found\n");

	if (cleaned)
		ft_free_matrix(cleaned);
	if (updated_envs)
		ft_free_matrix(updated_envs);
	megalodon_giga_chad_exit(127, 1);
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
    int r;

    if (!tree)
        return 1;
	static int please = 0;
    if (tree->cmds)
    {
        t_cmds *cmd = tree->cmds;
        while (cmd)
        {
            if (cmd->heredoc_done == 0 && please == 0)
            {
				please = 1;
                r = handle_heredoc(cmd);
                if (r != 0)
                {
                    cmd->flag_to_exec = 1;
					cmd->heredoc_done = 1;
                    return -1;
                }
                cmd->heredoc_done = 1;
            }
            cmd = cmd->next;
        }
    }
    check_order(tree->left, args, envp);
    check_order(tree->right, args, envp);
	please = 0;
    return 1;
}


void	reset_heredoc_flags(t_binary *tree)
{
	t_cmds	*cmd;

	if (!tree)
		return ;

	cmd = tree->cmds;
	while (cmd)
	{
		cmd->heredoc_done = 0;
		cmd = cmd->next;
	}
	reset_heredoc_flags(tree->left);
	reset_heredoc_flags(tree->right);
}


int exec_tree(t_binary *tree, char **args, char **envp)
{
    int ret_left;
    int co;

	// printf("===EXEC TREE\n");
    if (!tree)
        return 0;
    co = check_order(tree, args, envp);
    if (co < 0)
        return (btree()->global_signal == 130 ? 130 : 1);
    if (tree->cmds && tree->cmds->flag_to_exec == 1)
        return 1;
    if (btree()->global_signal == 130)
        return 130;
    if (tree->logic && ft_strcmp(tree->logic, "&&") == 0)
    {
        ret_left = exec_tree(tree->left, args, envp);
        if (ret_left == 0)
            return exec_tree(tree->right, args, envp);
        return ret_left;
    }
    if (tree->logic && ft_strcmp(tree->logic, "||") == 0)
    {
        ret_left = exec_tree(tree->left, args, envp);
        if (ret_left != 0)
            return exec_tree(tree->right, args, envp);
        return ret_left;
    }
    return exec_node(tree, args, envp);
}



