
#include "sigma_minishell.h"
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{

    builtin_env();
        return (1);
    while(1)
    {
        char *input = readline("minishell$ ");
        if (!input)
            break;
        add_history(input);
        
        char **args = ft_split(input, ' ');
        if (!args || !args[0])
        {
            free (input);
            free(args);
            continue;
        }
		if (parsing(input))
			printf("PODES SO POR TIPO PRINT ERROR POR AGORA\n");
        char *cmd = args[0];  
        if (is_builtin(cmd))  
            exec_builtin(cmd, args);
    }
    return(printf("Closing Minishell\n"), 0);
}