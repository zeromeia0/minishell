/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:05:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/06 15:41:26 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int handle_heredoc(t_cmds *cmd)
{
    t_cmds *cur = cmd;
    t_infile *in;
	printf("HANDLE HEREDOC\n");
    // signal(SIGINT, sig_handle_heredoc); <-- THIS FUCKER FUCKED MY WHOLE WEEKEND
    while (cur)
    {
        in = cur->infiles;
        while (in)
        {
            if (ft_strcmp(in->token, "<<") == 0)
            {
                if (manage_heredocs(cur) < 0)
                    return (-1);
            }
            in = in->next;
        }
        cur = cur->next;
    }
    return (0);
}



int	handle_regular_redirections(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (ft_strcmp(in->token, "<") == 0)
		{
			if (exec_single_left(in) < 0)
				return (1);
		}
		in = in->next;
	}
	if (exec_out_redirections(cmd->outfiles) < 0)
		return (-1);
	return (0);
}

void	pid_equal_zero_double(t_cmds *cmd, int p[2])
{
	close(p[0]);
	printf("PID EQUALS ZERO\n");
	signal(SIGINT, sig_handle_heredoc); //THIS IS DOING SOMETHING BAD
	process_all_heredocs(cmd->infiles, p);
	close(p[1]);
	megalodon_giga_chad_exit(0);
}
