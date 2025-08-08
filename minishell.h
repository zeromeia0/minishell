#ifndef MINISHELL_H
# define MINISHELL_H

<<<<<<< HEAD
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

=======
#include "my_libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef enum e_type{
    CMD,
    AND,
    OR
}   t_type;

typedef struct s_binary {
    t_type          type;
    struct s_binary *left;
    struct s_binary *right;
} t_binary;

typedef struct s_cmd{
    char **cmds;
    char *infile;
    char *outfile;
    char *err;
    int ret;
}   t_cmd;

int is_builtin(char *cmd);
void builtin_cd(char *path);
void builtin_pwd(void);
void    builtin_env(void);
int    builtin_exit(char **args);
int exec_builtin(char *cmd, char **args);

#endif
>>>>>>> main
