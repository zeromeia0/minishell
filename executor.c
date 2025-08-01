#include "minishell.h"
#include <readline/history.h>
#include <stdlib.h>

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


int main(int argc, char *argv[])
{
    t_binary *tree;

    tree = malloc(sizeof(t_binary));
    if (!tree)
        return (1);
    (void)argc;
    (void)argv;
    // exec_tree(tree);
    while(1)
    {
        char *input = readline("minishell$ ");
        if (!input)
            break;
        add_history(input);
        char **args = ft_split(input, ' ');  // You need a function like `ft_split` or `strtok` to tokenize the input
        char *cmd = args[0];  // The first token is the command itself

        if (is_builtin(cmd))  // Check if it's a built-in command
        {
            exec_builtin(cmd, args);  // Execute the corresponding built-in command
        }
    }
    return(printf("Closing Minishell\n"), 0);
}

