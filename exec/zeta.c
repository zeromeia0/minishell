/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:40:31 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/12 22:02:16 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	child_services(char **cleaned_cmd, char **envp, int status)
{
	if (ft_strcmp(cleaned_cmd[0], "exit") == 0)
		status = pipes_builtin_exit(cleaned_cmd, envp);
	status = exec_builtin(cleaned_cmd[0], cleaned_cmd, envp);
	ft_free_matrix(cleaned_cmd);
	ft_free_matrix(envp);
	megalodon_giga_chad_exit(status, 0);
}


void	file_descriptor_closer(int fd[2])
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}
int	get_heredoc_fd(t_cmds *cmd)
{
	t_infile	*in;

	in = cmd->infiles;
	while (in)
	{
		if (in->token && ft_strcmp(in->token, "<<") == 0)
			return (in->heredoc_fd);
		in = in->next;
	}
	return (-1);
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

int	pipes_builtin_exit(char **args, char **envp)
{
	long	status;

	printf("INSIDE PIPES BUILTIN EXIT\n");
	if (!args[1])
	{
		ft_free_matrix(envp);
		ft_free_matrix(args);
		if (btree()->global_signal)
			status = btree()->global_signal;
		else
			status = btree()->exit_status;
		update_shell_level(-1);
		megalodon_giga_chad_exit((unsigned char)status, 0);
	}
	if (!is_numeric(args[1]))
		return (my_ffprintf(args[1], "numeric argument required"), 0);
	if (args[0] && args[1] && args[2] != NULL)
		return (ft_putstr_fd("minishell: exit: too many arguments", 2), 0);
	status = ft_atol(args[1]);
	update_shell_level(-1);
	return (ft_free_matrix(envp), ft_free_matrix(args),
		megalodon_giga_chad_exit((unsigned char)status, 0), 0);
}


void	heredoc_setup(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd != -1)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	signal(SIGINT, sig_handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	write_heredoc_line(char *str, int fd[2])
{
	char	*expanded;

	if (!fd || !str)
		return ;
	if (btree()->cmds && btree()->cmds->infiles
		&& btree()->cmds->infiles->flag == 0)
		expanded = expand_hd(str);
	else
		expanded = str;
	write(fd[1], expanded, ft_strlen(expanded));
	write(fd[1], "\n", 1);
	if (expanded != str)
		free(expanded);
}

void	process_heredoc_lines(char *delimiter, int len, int fd[2])
{
	char	*str;

	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, len + 1))
	{
		write_heredoc_line(str, fd);
		free(str);
		if (btree()->global_signal == 130)
			megalodon_giga_chad_exit(130, 0);
		str = readline("> ");
	}
	if (!str && btree()->global_signal != 130)
		fprintf(stderr,
			"warning: here-document delimited by end-of-file (wanted `%s')\n",
			delimiter);
	free(str);
}


void	setup_signals_for_parent(void)
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_child(t_infile *in, int *p)
{
	signal(SIGINT, sig_handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(p[0]);
	get_single_heredoc(in->file, p);
	close(p[1]);
	megalodon_giga_chad_exit(0, 0);
}


void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_all_non_standart_fds(void)
{
	int	fd;

	fd = 2;
	while (++fd <= FOPEN_MAX)
		ft_close(fd);
}

void	megalodon_giga_chad_exit(int status, int flag)
{
	if (btree())
	{
		if (flag == 1)
			ft_free_matrix(btree()->env);
		free_os_envs();
		clear_env_list();
		close_all_non_standart_fds();
		binary_clear(btree());
		free(btree()->input);
	}
	exit(status);
}

void	children_killer(int status)
{
	exit(status);
}

void	check_commands(char *cmd)
{
	if (btree()->cmds->flag_to_exec == 1)
		megalodon_giga_chad_exit(126, 0);
	if (access(cmd, F_OK) != 0)
	{
		my_ffprintf(cmd, "No such file or directory\n");
		megalodon_giga_chad_exit(127, 0);
	}
}

void	double_helper(int status, int p[2], pid_t pid)
{
	close(p[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	// printf("restarting signal 4\n"), restart_signals();
}

int	check_cmds(t_cmds *cmds, char **args, char **envp)
{
	t_cmds *current;

	if (!cmds || !cmds->cmd)
		return (1);
	current = cmds;
	while (current)
	{
		if (!is_cmd_valid(current, args, envp))
			return (127);
		current = current->next;
	}
	return (1);
}
