#ifndef MINISHELL_H
# define MINISHELL_H

#include "./pipex/my_libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct s_cmd{
    char **args;
    char *infile;
    char *outfile;
    char *append;
    int ret;
}   t_cmd;


#endif