#ifndef JOJOMINISHELL_H
# define JOJOMINISHELL_H

#include "parse/jojo_libft/libft.h"
#include "exec/minishell.h"
#include "exec/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// << = 256
// >> = 255

typedef struct s_outfile
{
	int					fd;
	int					token;
	char				*file;
	struct s_outfile	*next_file;
}	t_outfile;

typedef struct s_infile
{
	int				token;
	char			*file;
	struct s_infile	*next_file;
}	t_infile;


typedef struct s_cmds
{
	char			**comd;
	t_outfile			*outfiles;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_table
{
	char	**infiles;
	t_cmds	*cmds;
}	t_table;

typedef struct s_binary
{
    t_type          type;
	char			logic; // & |
	int				left_ret;
	int				right_ret;
	t_table			*table;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
}	t_binary;

t_table *parsing(char *str);

#endif

/* cat in > out in in in in in in in in in */

/* cat Makefile > o1 | cat Makefile > o2 | cat Makefile > o3 */
