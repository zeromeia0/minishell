/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:43:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/10 19:04:39 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	cmd->heredoc_done = 1;
	if (first_fd != -1)
	{
		if (dup2(first_fd, STDIN_FILENO) == -1)
			children_killer(1); /* or handle error properly */
	}
	if (cmd->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			children_killer(1); /* or handle error properly */
	}
	if (cmd->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (first_fd != -1)
		close(first_fd);
}


void execute_child(t_cmds *cmd, int first_fd, int fd[2], char **env)
{
    char **cleaned_cmd;
    int status;

    setup_child_fds(first_fd, fd, cmd);
    cleaned_cmd = array_to_exec(cmd);
    if (!cleaned_cmd || !cleaned_cmd[0])
    {
        ft_free_matrix(cleaned_cmd);
        children_killer(127);
    }

    if (is_builtin(cleaned_cmd[0]))
    {
        if (ft_strcmp(cleaned_cmd[0], "exit") == 0)
            status = pipes_builtin_exit(cleaned_cmd, env);
        status = exec_builtin(cleaned_cmd[0], cleaned_cmd, env);
        ft_free_matrix(cleaned_cmd);
        megalodon_giga_chad_exit(status, 0);
    }
    else
    {
        exec_path(cleaned_cmd[0], cleaned_cmd, env);
        ft_free_matrix(cleaned_cmd);
        children_killer(127);
    }
}


int	setup_pipe(t_cmds *cmd, int *first_fd, int fd[2])
{
	if (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
	}
	return (0);
}

int	process_command(t_cmds *cmd, int *first_fd, char **env)
{
	// printf("PROCESSING COMMAND");
	int		fd[2];
	pid_t	pid;
	if (cmd->cmd == NULL)
		cmd->flag_to_exec = 1;
	if (cmd->flag_to_exec == 0)
	{
		if (setup_pipe(cmd, first_fd, fd) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
			execute_child(cmd, *first_fd, fd, env);
		if (*first_fd != -1)
			close(*first_fd);
		if ((cmd)->next != NULL)
		{
			close(fd[1]);
			*first_fd = fd[0];
		}
	}
	return (0);
}

int	has_heredocs(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			return (1);
		in = in->next;
	}
	return (0);
}
