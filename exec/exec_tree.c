/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/25 14:38:37 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec_child(t_cmds *cmd)
{
	char	**cleaned;
	char	**updated_envs;

	signal(SIGINT, handle_sigint);
	cleaned = array_to_exec(cmd);
	updated_envs = list_to_char(*get_env_list());
	if (has_redir(cmd))
		exec_redirections(cmd);
	if (has_builtin(cmd))
		exit(exec_builtin(cleaned[0], cleaned, updated_envs));
	else
		exec_path(cleaned[0], cleaned, updated_envs);
	free_matrix(cleaned);
	free_matrix(updated_envs);
}

int	exec_single_cmd(t_cmds *cmd)
{
	pid_t	pid;
	int		status;

	if (has_builtin(cmd) && !has_redir(cmd))
		return (exec_single_cmd_aux(cmd));
	pid = fork();
	if (pid == 0)
		exec_child(cmd);
	else
	{
		signal(SIGINT, set_to_onethirty);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			btree()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			btree()->exit_status = 130;
		return (btree()->exit_status);
	}
	return (1);
}

static int	exec_subshell(t_binary *subshell, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(exec_tree(subshell, args, envp));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 128 + WTERMSIG(status);
	return (btree()->exit_status);
}

int	exec_node(t_binary *node, char **args, char **envp)
{
	if (!node)
		return (0);
	// if (node->cmds->cmd == NULL)
	// 	node->cmds->flag_to_exec = 1;
	if (node->cmds != NULL/*  && node->cmds->flag_to_exec == 0 */)
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

char **buildup_path(t_cmds *cmd, char **args, char **envp)
{
	char **final_str;
	char **paths_to_search;
	int i = 0;
	
	if (cmd->cmd == NULL || cmd->flag_to_exec == 0)
		return (NULL);
	paths_to_search = get_paths_to_search(envp);
	final_str = malloc(sizeof(char *) * (ft_matlen(envp) + 1));
	if (has_builtin(cmd))
	{
		final_str[0] = ft_strdup(*cmd->cmd);
		final_str[1] = NULL;
		return (final_str);
	}
	else if (is_system_path_command(cmd->cmd[0], envp))
	{
		while (paths_to_search[i])
		{
			char *tmp = ft_strjoin(paths_to_search[i], "/");
			final_str[i] = ft_strjoin(tmp, cmd->cmd[0]);
			free(tmp);
			i++;
		}
		final_str[i] = NULL;
	}
	return (final_str);
}

int	check_order(t_binary *tree, char **args, char **envp)
{
	t_infile	*current_infile;
	t_cmds		*current_cmds;
	t_outfile	*current_outfile;

	if (!tree->cmds || !tree->cmds->infiles)
		return (0);
	current_infile = tree->cmds->infiles;
	while (current_infile)
	{
		if (access(current_infile->file, F_OK) != 0
			|| access(current_infile->file, R_OK) != 0)
			return (printf("infile non existent\n"), 0);
		current_infile = current_infile->next;
	}
	if (!tree->cmds->cmd)
		return (0);
	current_cmds = tree->cmds;
	while (current_cmds)
	{
		char	**something = buildup_path(current_cmds, args, envp);
		int		i = 0;
		int		valid = 0;

		while (something && something[i])
		{
			if (access(something[i], F_OK) == 0 && access(something[i], X_OK) == 0)
			{
				valid = 1;
				break;
			}
			i++;
		}
		if (something)
			ft_free_matrix(something);
		if (!valid)
			return (printf("command not found or not executable\n"), -1);
		current_cmds = current_cmds->next;
	}
	if (!tree->cmds->outfiles)
		return (0);
	current_outfile = tree->cmds->outfiles;
	if (current_outfile->file == NULL)
		exec_out_redirections(current_outfile);
	while (current_outfile)
	{
		if (access(current_outfile->file, W_OK) != 0)
			return (printf("no permissions fella\n"), 0);
		current_outfile = current_outfile->next;
	}
	return (1);
}


// < in1 < in2 /bin/cat > out1 > out2
// < in1 < in2 cat > out1 > out2
// < in7 < in2 /bin/cat > out1 > out2 | ls <-- why infinite loop


int	exec_tree(t_binary *tree, char **args, char **envp)
{
	int	ret_left;

	check_order(tree, args, envp);
	if (btree()->global_signal == 130)
		return (130);
	if (!tree)
		return (0);
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
