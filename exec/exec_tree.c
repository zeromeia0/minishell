/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:55:08 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/29 09:42:27 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int cmd_has_heredoc(t_cmds *cmd)
{
    t_infile *in = NULL;

    if (!cmd)
        return 0;
    in = cmd->infiles;
    while (in)
    {
        if (in->token && ft_strcmp(in->token, "<<") == 0)
            return 1;
        in = in->next;
    }
    return 0;
}


static void	exec_child(t_cmds *cmd)
{
	char	**cleaned;
	char	**updated_envs;

	if (cmd->flag_to_exec == 1)
		return ;
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

int exec_single_cmd(t_cmds *cmd)
{
    pid_t   pid;
    int     status;
    int     shell_should_ignore = 0;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    if (!cmd || !cmd->cmd)
        return (btree()->exit_status);
    if (cmd->flag_to_exec == 1)
        return (btree()->exit_status);
    if (has_builtin(cmd) && !has_redir(cmd))
        return (exec_single_cmd_aux(cmd));
    if (cmd_has_heredoc(cmd))
    {
        shell_should_ignore = 1;
        signal(SIGINT, SIG_IGN);
    }

    pid = fork();
    if (pid == 0)
        exec_child(cmd);
    else
    {
        if (!shell_should_ignore)
            signal(SIGINT, set_to_onethirty);
        waitpid(pid, &status, 0);
        if (shell_should_ignore)
            restart_signals();
        else
            restart_signals();
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

char **buildup_path(t_cmds *cmd, char **args, char **envp)
{
    char **final_str;
    char **paths_to_search;
    int i = 0;
    int path_count;

    paths_to_search = get_paths_to_search(envp);
    path_count = ft_matlen(paths_to_search);
    final_str = malloc(sizeof(char *) * (path_count + 1));
    if (!final_str)
        return NULL;

    if (has_builtin(cmd))
    {
        final_str[0] = ft_strdup(cmd->cmd[0]);
        final_str[1] = NULL;
        return final_str;
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
    return final_str;
}


int ensure_outfile(t_outfile *out)
{
    int fd;

    if (!out || !out->file)
        return -1;

    fd = open(out->file, O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        // Failed to open or create → maybe permission issue in directory
        return btree()->cmds->flag_to_exec = 1,
               my_ffprintf(out->file, "Permission denied\n"), -1;
    }
    close(fd); // Close immediately; actual redirection happens in exec_out_redirections
    return 0;
}
int check_order(t_binary *tree, char **args, char **envp)
{
    t_infile    *current_infile;
    t_cmds      *current_cmds;
    t_outfile   *current_outfile;

    if (!tree->cmds)
        return (0);
	if (handle_heredocs(tree->cmds) < 0)
		return (btree()->cmds->flag_to_exec = 1, -1);
    current_infile = tree->cmds->infiles;
    while (current_infile)
    {
        if (ft_strncmp(current_infile->token, "<<", 2) != 0) // skip heredocs
        {
            if (access(current_infile->file, F_OK) != 0)
                return (btree()->cmds->flag_to_exec = 1,
                        my_ffprintf(current_infile->file, "No such file or directory 1\n"), 0);
            if (access(current_infile->file, R_OK) != 0)
                return (btree()->cmds->flag_to_exec = 1,
                        my_ffprintf(current_infile->file, "Permission denied\n"), 0);
        }
        current_infile = current_infile->next;
    }
    if (!tree->cmds->cmd)
        return (0);
    current_cmds = tree->cmds;
    while (current_cmds)
    {
        char    **something = buildup_path(current_cmds, args, envp);
        int     i = 0;
        int     valid = 0;

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
            return (0);
        current_cmds = current_cmds->next;
    }
    if (!tree->cmds->outfiles)
        return (0);
    current_outfile = tree->cmds->outfiles;
    while (current_outfile)
    {
        if (ensure_outfile(current_outfile) < 0)
            return 0;
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

	if (btree()->cmds && btree()->cmds->flag_to_exec == 1)
		return (0);
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
