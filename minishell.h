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


#endif