#ifndef MINISHELL_H
# define MINISHELL_H

#include "parse/jojo_libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// << = 256
// >> = 255

typedef struct s_outfile
{
	int		fd;
	int		token;
	char	*file;
}	t_outfile;

typedef struct s_cmds
{
	char		**comd;
	t_outfile	*outfile;
	t_cmds		*next;
}	t_cmds;

typedef struct s_table
{
	char	**infiles;
	t_cmds	*cmds;
}	t_table;

typedef struct s_binary
{
	char          	logic;
	int				left_ret;
	int				right_ret;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
	t_table			*table;
}	t_binary;

t_table *parsing(void);

#endif

/* cat in > out in in in in in in in in in */

/* cat Makefile > o1 | cat Makefile > o2 | cat Makefile > o3 */

