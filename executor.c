#include "minishell.h"
#include <unistd.h>

int    executor(t_cmd *cmd_table)
{
    return ((cmd_table->append) == 0);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    // while(1)
    // {
    //     read(STDIN_FILENO, "0000000000", 10);
    //     printf("lido\n");
    // }
    return(printf("Salve\n"), 0);
}