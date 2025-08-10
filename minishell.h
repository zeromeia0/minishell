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

typedef struct s_token
{
	char	**stokens;
	char	**dtokens;
	char	**ttokens;
	char	**qtokens;
}	t_token;

typedef struct s_outfile
{
	char				*token;
	char				*file;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_infile
{
	char 			*token;
	char			*file;
	struct s_infile	*next;
}	t_infile;

typedef struct s_cmds
{
	char			**cmd;
	t_outfile		*outfiles;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_table
{
	t_infile	*infiles;
	t_cmds		*cmds;
}	t_table;

typedef struct s_binary
{
	t_type			type;
	int				sublvl;
	int				left_ret;
	int				right_ret;
	int				subshell_ret;
	t_table			*table;
	struct s_binary	*up;
	struct s_binary	*left;
	struct s_binary	*right;
	struct s_binary	*subshell;
}	t_binary;

int			parsing(char *str);
t_binary	*btree(void);

// clear everything inside the data struct
void		binary_clear(t_binary *binary);
void		table_clear(t_table *table);
void		cmds_clear(t_cmds *cmds);
void		outfile_clear(t_outfile *outfile);
void		infile_clear(t_infile *infile);

// create the data struct with the information needed (use NULL where available if needed)
t_binary	*binary_new(int shlvl, t_type type, t_table *up, t_table *table);
t_table		*table_new(t_cmds *cmds, t_infile *infile);
t_cmds		*cmds_new(char **cmd, t_outfile *outfile);
t_outfile	*outfile_new(char *file, char *token);
t_infile	*infile_new(char *file, char *token);

void	create_binary_tree(char **mat, int	shlvl, t_binary *tree);

#endif

/* cat in > out in in in in in in in in in */

/* cat Makefile > o1 | cat Makefile > o2 | cat Makefile > o3 */

// < in cat Makefile > out | cat Makefile > out1
