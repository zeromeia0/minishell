#ifndef MINISHELL_H
# define MINISHELL_H

#include "parse/jojo_libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_binary
{
	int          	token;
	struct s_binary	*left;
	struct s_binary	*right;
	int				ret;
}	t_binary;

char **parsing(void);

#endif
