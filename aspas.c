#include "minishell.h"
#include "my_libft/libft.h"

bool even_odd_aspas(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == '"')
            count++;
        i++;
    }
    return (count % 2 == 0);
}

char *aspas(char *str)
{
    if (!str || str[0] == '\0')
        return (NULL);
    char *new_str = str;
    char *tmp;
    while (!even_odd_aspas(new_str))
    {
        tmp = readline("> ");
        if (!tmp)
            break;
        if (tmp[0] == '"')
        {
            new_str = ft_strjoin_free(new_str, tmp + 1, 1);
            free(tmp);
            break;
        }
        new_str = ft_strjoin_free(new_str, "\n", 1);
        new_str = ft_strjoin_free(new_str, tmp, 1);
        free(tmp);
    }
    return (new_str);
}