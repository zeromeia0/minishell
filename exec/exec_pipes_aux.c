/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:43:18 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/12 21:43:48 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "minishell.h"

void	setup_child_fds(int first_fd, int fd[2], t_cmds *cmd)
{
	int	heredoc_fd;

	heredoc_fd = get_heredoc_fd(cmd);
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (first_fd != -1)
	{
		dup2(first_fd, STDIN_FILENO);
		close(first_fd);
	}
	if (cmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

void	execute_child(t_cmds *cmd, int first_fd, int fd[2], char **env)
{
	char	**cleaned_cmd;
	int		status;

	if (has_redir(cmd))
		exec_redirections(cmd);
	setup_child_fds(first_fd, fd, cmd);
	cleaned_cmd = array_to_exec(cmd);
	if (!cleaned_cmd || !cleaned_cmd[0])
	{
		ft_free_matrix(cleaned_cmd);
		megalodon_giga_chad_exit(127, 0);
	}
	if (is_builtin(cleaned_cmd[0]))
		child_services(cleaned_cmd, env, status);
	else
	{
		exec_path(cleaned_cmd[0], cleaned_cmd, env);
		ft_free_matrix(cleaned_cmd);
		megalodon_giga_chad_exit(127, 0);
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

int process_command(t_cmds *cmd, int *first_fd, char **env)
{
    int fd[2];
    pid_t pid;

    fd[0] = -1;
    fd[1] = -1;
    if (cmd->cmd == NULL)
        cmd->flag_to_exec = 1;
    if (cmd->flag_to_exec == 0)
    {
        if (setup_pipe(cmd, first_fd, fd) == -1)
            return (-1);
        pid = fork();
        if (pid == 0)
            execute_child(cmd, *first_fd, fd, env);
        if (*first_fd >= 0)
            close(*first_fd);
        if (cmd->next != NULL)
        {
            if (fd[1] >= 0)
                close(fd[1]);
            *first_fd = fd[0];
        }
        else
            file_descriptor_closer(fd);
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
