#include "sigma_minishell.h"


int exec_tree(t_binary *tree)
{
    int left;

    if (!tree)
        return (0);
    if (tree->type == CMD)
         printf("CMD detected\n");
    left = exec_tree(tree->left);
    if (tree->type == AND)
    {
        printf("AND character dettected\n");
        if (left == 0)
            return (exec_tree(tree->right));
        else
            return (left);      
    }
    if (tree->type == OR)
    {
        printf("OR character detected\n");
        if (left != 0)
            return (exec_tree(tree->right));
        else
            return left;
    }
    return (1);
}


// int main(int argc, char *argv[], char **envp)
// {
//     (void)argc;
//     (void)argv;

//     builtin_env(); // Initialize environment if needed

//     while (1)
//     {
//         char *input = readline("minishell$ ");
//         if (!input)
//         {
//             printf("exit\n");
//             break;
//         }
//         add_history(input);
//         char **args = ft_split(input, ' ');
//         if (!args || !args[0])
//         {
//             free(input);
//             free(args);
//             continue;
//         }
//         char *cmd = args[0];
//         if (is_builtin(cmd))
//             exec_builtin(cmd, args);
//         else
//             exec_path(cmd, args, envp);
//         free(input);
//         free(args);
//     }
//     return (printf("Closing Minishell\n"), 0);
// }

