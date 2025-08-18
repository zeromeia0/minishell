#include "sigma_minishell.h"


// int exec_tree(t_binary *tree)
// {
//     int left;

//     if (!tree)
//         return (0);
//     if (tree->type == CMD)
//          printf("CMD detected\n");
//     left = exec_tree(tree->left);
//     if (tree->type == AND)
//     {
//         printf("AND character dettected\n");
//         if (left == 0)
//             return (exec_tree(tree->right));
//         else
//             return (left);      
//     }
//     if (tree->type == OR)
//     {
//         printf("OR character detected\n");
//         if (left != 0)
//             return (exec_tree(tree->right));
//         else
//             return left;
//     }
//     return (1);
// }


// int main(int argc, char *argv[], char **envp)
// {
// 	// (void)envp;
// 	printf("Arg count: %d\n", argc);
// 	int i = 0;
// 	// if (argv[1] == NULL)
// 	// 	return (printf("no argv\n"), 0);
// 	printf("ARGS: \n");
// 	while (argv[i])
// 		{
// 			printf("%s", argv[i]);
// 			i++;
// 		}
// 	printf("\nENVP: \n");
// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("ENV[%d]: %s\n", i, envp[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int main(int argc, char *argv[], char **envp)
// {
//     t_binary *tree;

//     builtin_env();
//     tree = malloc(sizeof(t_binary));
//     if (!tree)
//         return (1);
//     (void)argc;
//     (void)argv;
//     // exec_tree(tree);
//     while(1)
//     {
//         char *input = readline("minishell$ ");
//         if (!input)
//             break;
//         add_history(input);
        
//         char **args = ft_split(input, ' ');
//         if (!args || !args[0])
//         {
//             free (input);
//             free(args);
//             continue;
//         }
//         char *cmd = args[0];  
//         if (is_builtin(cmd))  
//             exec_builtin(cmd, args);
//     }
//     return(printf("Closing Minishell\n"), 0);
// }

