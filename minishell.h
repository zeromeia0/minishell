#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_cmd{
    char **args;
    char *infile;
    char *outfile;
    char *append;
    int ret;
}   t_cmd;


#endif