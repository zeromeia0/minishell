/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:49:36 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/01 10:49:40 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void	print_infiles(t_infile *file)
{
	while (file)
	{
		printf("%s %s\n", file->token, file->file);
		file = file->next;
	}
}

void	print_outfiles(t_outfile *file)
{
	while (file)
	{
		printf("%s %s\n", file->token, file->file);
		file = file->next;
	}
}

void	print_cmds(t_cmds *cmds)
{
	while (cmds)
	{
		printf("==================\n");
		printf("\t\tstarts infile\n");
		print_infiles(cmds->infiles);
		printf("\t\tend infile\n");
		printf("\t\tstarts commands\n");
		ft_print_matrix(cmds->cmd);
		printf("\t\tend commands\n");
		printf("\t\tstarts outfiles\n");
		print_outfiles(cmds->outfiles);
		printf("\t\tend outfiles\n");
		printf("==================\n");
		cmds = cmds->next;
	}
}

void	print_tree(t_binary *tree, int sub)
{
	// if (sub)
	// printf( "\nentering subshell\n");
	if (tree == NULL)
		return ;
	print_tree(tree->subshell, 1);
	print_tree(tree->left, 0);
	print_tree(tree->right, 0);
	if (tree->left == NULL && tree->right == NULL)
		if (tree->cmds)
			print_cmds(tree->cmds);
	if (sub)
		printf("\n^exiting shubshell^\n");
}

t_binary	*btree(void)
{
	static t_binary	tree;

	return (&tree);
}

static void	initialize_stuff(int argc, char *argv[], char **envp)
{
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &btree()->orig_termios);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	builtin_env(envp);
	if (am_i_truly_myself(argv[0]))
		update_shell_level(1);
	btree()->env = list_to_char(*get_env_list());
	btree()->os_env = *get_env_list();
	enhanced_sorting_stoled_from_jlima(btree()->os_env);
}

int	main(int argc, char *argv[], char **envp)
{
	initialize_stuff(argc, argv, envp);
	while (1)
	{
		btree()->input = readline("minishell$ ");
		if (!btree()->input)
			break ;
		/* printf("restart ONE\n"),  */restart_signals();
		add_history(btree()->input);
		if (*btree()->input == '\0')
		{
			free(btree()->input);
			continue ;
		}
		if (parsing(btree()->input) == 0)
		{
			// print_tree(btree(), 0);
			btree()->main_exit = exec_tree(btree(), argv, btree()->env);
			/* printf("restart TWO\n"),  */restart_signals();
			free(btree()->input);
			binary_clear(btree());
		}
	}
	ft_free_matrix(btree()->env);
	// btree()->env = NULL;
	free_os_envs();
	return (clear_env_list(), printf("Closing Minishell\n"),
		btree()->exit_status);
}
