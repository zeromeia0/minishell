#include "minishell.h"
#include "my_libft/libft.h"
#include <unistd.h>

int is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "exit", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "unset", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", 6) == 0)
        return (1);
    return (0);
}

void builtin_cd(char *path)
{
    if (chdir(path) != 0)
        perror("cd");
}

void builtin_pwd(void)
{
    char buf[1024];
    if (getcwd(buf, sizeof(buf)) == NULL)
        perror("pwd");
    else
        printf("%s\n", buf);
}

void    builtin_env(void)
{
    int i;
    extern char **environ;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

// void builtin_echo(char *str)
// {
//     printf("")
// }

int    builtin_exit(char **args)
{
    int status;

    status = 0;
    if (args[1])
        status = ft_atoi(args[1]);
    // printf("status: %d\n", status);
    return (status);
}

int exec_builtin(char *cmd, char **args)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
    {
        if (args[1] == NULL)
            {
                printf("cd: missing path\n");
                return (0);
            }
        else
            builtin_cd(args[1]);
    }
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        builtin_pwd();
    else if (ft_strncmp(cmd, "env", 3) == 0)
        builtin_env();
    // else if (ft_strncmp(cmd, "echo", 4))
    //     bu
    else if (ft_strncmp(cmd, "exit", 4) == 0)
        builtin_exit(args);
    return (0);
}