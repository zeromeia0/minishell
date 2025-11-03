/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:35:39 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/03 14:46:43 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "parse/jojo_libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_wild
{
	char			*file;
	char			*search;
	char			d_type;
	struct s_wild	*next;
}					t_wild;

typedef struct s_token
{
	char	**stokens;
	char	**dtokens;
	char	**sep;
}			t_token;

typedef struct s_outfile
{
	char				*token;
	char				*file;
	struct s_outfile	*next;
}						t_outfile;

typedef struct s_infile
{
	int				heredoc_fd;
	int				flag;
	char			*token;
	char			*file;
	struct s_infile	*next;
}					t_infile;

typedef struct s_os_envs
{
	char				*linux_envs;
	char				*temp_vars;
	struct s_os_envs	*next;
}						t_os_envs;

typedef struct s_cmds
{
	int					heredoc_done;
	int					expanded;
	int					flag_to_exec;
	int					export_flag;
	char				**cmd;
	t_infile			*infiles;
	t_outfile			*outfiles;
	struct s_cmds		*next;
}						t_cmds;

typedef enum e_type
{
	CMD,
	AND,
	OR,
	EMPTY,
	ERROR
}	t_type;

typedef struct s_binary
{
	char			*logic;
	int				sublvl;
	char			*input;
	int				left_ret;
	int				right_ret;
	char			*print_cmd;
	int				subshell_ret;
	int				main_exit;
	int				global_signal;
	int				exit_status;
	char			**mat;
	char			**env;
	t_type			type;
	t_cmds			*cmds;
	t_os_envs		*os_env;
	struct stat		self_stat;
	struct stat		cmd_stat;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
	struct termios	orig_termios; //<-- VINI TESTEANDO UMA CRAZY THING
}					t_binary;

#endif