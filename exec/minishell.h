#ifndef MINISHELL_H
#define MINISHELL_H

#include "../my_libft/libft.h"
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
    OR,
	EMPTY,
	ERROR
}   t_type;

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

