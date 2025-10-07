/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:11:44 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/07 07:11:04 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../sigma_minishell.h"

int	count_heredocs(t_infile *in)
{
	int	count;

	count = 0;
	while (in)
	{
		if (ft_strcmp(in->token, "<<") == 0)
			count++;
		in = in->next;
	}
	return (count);
}

void get_single_heredoc(char *eof, int fd[2])
{
    char    *str;
    char    *delimiter;
    int     len;
    int     tty_fd;
    char    *expanded;

    delimiter = remove_aspas(eof);
    len = ft_strlen(delimiter);
    if (btree()->global_signal == 130)
        exit(130);
        // megalodon_giga_chad_exit(130);
    tty_fd = open("/dev/tty", O_RDONLY);
    if (tty_fd != -1)
    {
        dup2(tty_fd, STDIN_FILENO);
        close(tty_fd);
    }
    signal(SIGINT, sig_handle_heredoc); //not the cuprit
    signal(SIGQUIT, SIG_IGN);
    str = readline("> ");
    while (str && ft_strncmp(str, delimiter, len + 1))
    {
        if (fd) // only write if fd is provided
        {
            if (btree()->cmds && btree()->cmds->infiles && btree()->cmds->infiles->flag == 0)
                expanded = expand_hd(str);
            else
                expanded = str;
            write(fd[1], expanded, ft_strlen(expanded));
            write(fd[1], "\n", 1);
            if (expanded != str)
                free(expanded);
        }
        free(str);
        if (btree()->global_signal == 130)
            exit(130);
            // megalodon_giga_chad_exit(130);
        str = readline("> ");
    }
    if (!str && btree()->global_signal != 130)
        fprintf(stderr,
            "warning: here-document delimited by end-of-file (wanted `%s')\n",
            delimiter);
    free(str);
    free(delimiter);
    if (fd)
        close(fd[1]);
}


void	process_heredoc_recursive_simple(t_infile *current, int fd[2])
{
	if (!current)
		return ;
	if (ft_strcmp(current->token, "<<") == 0)
		get_single_heredoc(current->file, fd);
	process_heredoc_recursive_simple(current->next, fd);
}

void process_all_heredocs(t_infile *in, int p[2])
{
    t_infile *current = in;
    int       tmp_pipe[2];

    while (current)
    {
        if (ft_strcmp(current->token, "<<") == 0)
        {
            if (pipe(tmp_pipe) == -1)
            {
                perror("pipe");
                exit (1);
                // megalodon_giga_chad_exit(1);
            }

            get_single_heredoc(current->file, tmp_pipe);

            close(tmp_pipe[1]);           // close write end
            current->heredoc_fd = tmp_pipe[0]; // store read end
        }
        current = current->next;
    }
}

int manage_heredocs(t_cmds *cmd)
{
    t_cmds      *cur;
    t_infile    *in;
    int         p[2];
    pid_t       pid;
    int         status;

    cur = cmd;
    while (cur)
    {
        in = cur->infiles;
        while (in)
        {
            if (ft_strcmp(in->token, "<<") == 0)
            {
                if (pipe(p) == -1)
                    return (perror("pipe"), -1);

                pid = fork();
                if (pid == -1)
                    return (perror("fork"), -1);

                if (pid == 0)
                {
                    // CHILD → reads heredoc
                    signal(SIGINT, sig_handle_heredoc);
                    signal(SIGQUIT, SIG_IGN);
                    close(p[0]);
                    get_single_heredoc(in->file, p);
                    close(p[1]);
                    _exit(0);
                }
                else
                {
                    // PARENT → waits for heredoc result
                    close(p[1]);
                    waitpid(pid, &status, 0);

                    if (WIFSIGNALED(status) ||
                        (WIFEXITED(status) && WEXITSTATUS(status) == 130))
                    {
                        close(p[0]);
                        btree()->global_signal = 130;
                        btree()->exit_status = 130;
                        // DO NOT restart signals here!
                        return (-1);
                    }

                    // Success case → restore signals normally
                    restart_signals();
                    in->heredoc_fd = p[0];
                }
            }
            in = in->next;
        }
        cur = cur->next;
    }
    return (0);
}




