#include "minishell.h"

int    executor(t_cmd *cmd_table)
{
    return ((cmd_table->append) == 0);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    while(1)
    {
        char *line = readline("minishell$ ");
        if (!line)
            break;
    }
    return(printf("Closing Minishell\n"), 0);
}