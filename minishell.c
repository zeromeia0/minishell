
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>

t_binary	*btree(void)
{
	static	t_binary	tree;

	return (&tree);
}

int main(int argc, char *argv[], char **envp)
{
    (void)argc;
    (void)argv;

    builtin_env();

    while (1)
    {
        char *input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        add_history(input);
		parsing(input);
        char **args = ft_split(input, ' ');
        if (!args || !args[0])
        {
            free(input);
            free(args);
            continue;
        }
        char *cmd = args[0];
        if (is_builtin(cmd))
            exec_builtin(cmd, args);
        else
            exec_path(cmd, args, envp);
        free(input);
        free(args);
    }
    return (printf("Closing Minishell\n"), 0);
}
