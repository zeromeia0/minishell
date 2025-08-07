#ifndef MINISHELL_H
# define MINISHELL_H

#include "parse/jojo_libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// << = 256
// >> = 255

typedef struct s_file
{
	int		fd;
	int		token;
	char	*file;
}	t_file;

typedef struct s_cmds
{
	int		fd;
	int		token;
	char	*file;
}	t_cmds;

typedef struct s_table
{
	t_file	*infiles;
	t_file	*outfiles;
	t_cmds	*cmds;
}	t_table;

typedef struct s_binary
{
	char          	logic;
	int				left_ret;
	int				right_ret;
	struct s_binary	*left;
	struct s_binary	*right;
	t_table			*table;
}	t_binary;

t_table *parsing(void);

#endif

/* cat in > out in in in in in in in in in */

/* cat in > out | c*/

/* cat Makefile > o1 | cat Makefile > o2 | cat Makefile > o3 */

