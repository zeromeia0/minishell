#include "sigma_minishell.h"

char *find_path(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return (strdup(envp[i] + 5));
        i++;
    }
    return (NULL);
}

char **split_path(char **envp)
{
    char *path = find_path(envp);
    if (!path)
        return (NULL);
    char **vars = ft_split(path, ':');
    free(path);
    return (vars);
}

void execute_path(char *cmd, char **args, char **envp)
{
    if (!cmd)
    {
        write(2, "No command provided\n", 20);
        return;
    }
    char **paths_to_search = split_path(envp);
    if (!paths_to_search)
    {
        write(2, "PATH not found in environment\n", 28);
        return;
    }
    int i = 0;
    while (paths_to_search[i])
    {
        int full_path_len = strlen(paths_to_search[i]) + strlen(cmd) + 2;
        char *full_path = malloc(full_path_len);
        if (!full_path)
        {
            perror("malloc failed");
            break;
        }
        snprintf(full_path, full_path_len, "%s/%s", paths_to_search[i], cmd);

        if (access(full_path, X_OK) == 0)
        {
            execve(full_path, args, envp);
            perror("execve failed");
            free(full_path);
            break;
        }
        free(full_path);
        i++;
    }
    i = 0;
    while (paths_to_search[i])
        free(paths_to_search[i++]);
    free(paths_to_search);
    write(2, "command not found\n", 18);
}

int main(int argc, char *argv[], char **envp)
{
    if (argc < 2)
    {
        write(2, "Usage: ./minishell <command>\n", 29);
        return (1);
    }
    execute_path(argv[1], &argv[1], envp); // Pass &argv[1] to skip "./minishell"
    return (0);
}