/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:19:21 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/08 09:09:45 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	help_to_process(t_cmds *cmd, int p[2])
{
	close(p[0]);
	printf("pipes\n");
	signal(SIGINT, sig_handle_heredoc);
	process_all_heredocs(cmd->infiles, p);
	close(p[1]);
	children_killer(0);
}

int	process_command_heredocs(t_cmds *cmd)
{
	int		p[2];
	pid_t	pid;
	int		status;

	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	if (pipe(p) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
		help_to_process(cmd, p);
	else
	{
		close(p[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		// printf("restarting signal 2\n"),restart_signals();
		close(p[0]);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (btree()->exit_status = 130, -1);
	}
	return (0);
}


int process_heredocs_and_checks(t_cmds *cmd)
{
    t_cmds *current = cmd;

    while (current)
    {
        if (has_heredocs(current))
        {
            if (manage_heredocs(current) < 0)
            {
                btree()->exit_status = 130;
                return (btree()->exit_status);
            }
        }
        current = current->next;
    }
    if (btree()->global_signal == 130)
        return 130;
    return 0;
}


int	exec_pipes(t_cmds *cmd, char **env)
{
	int		first_fd;
	int		status;
	t_cmds	*current;

	if (btree()->global_signal == 130 || (btree()->cmds && btree()->cmds->flag_to_exec == 1))
		return (btree()->exit_status);
	printf("===EXECUTING PIPES\n");
	first_fd = -1;
	// if (!cmd || cmd->cmd[0] == NULL)
	// 	return (printf("NO COMMAND\n"), 0);
	current = cmd;
	// printf("%d\n", 0);
	// if (process_heredocs_and_checks(cmd) < 0)
    // 	return (btree()->exit_status);
	while (current)
	{
		// printf("%d\n", 1);
		if (process_command(current, &first_fd, env) == -1)
			return (printf("COULDN'T PROCESS IT\n"), -1);
		current = current->next;
	}
	// printf("%d\n", 2);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		btree()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		btree()->exit_status = 128 + WTERMSIG(status);
	return (btree()->exit_status);
}
