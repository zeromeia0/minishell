#include "my_libft/libft.h"
#include "sigma_minishell.h"


int count_it(char *str, int c)
{
	int i = 0;
	int count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char *remove_it(char *str, int c)
{
    int i = 0;
    int j = 0;
	if (!str)
		return (NULL);
    int count = count_it(str, c);
    char *removed = malloc(ft_strlen(str) + 1 - count);
    if (!removed)
        return (NULL);

    while (str[i])
    {
        if (str[i] != c)
        {
            removed[j] = str[i];
            j++;
        }
        i++;
    }
    removed[j] = '\0';
    return (removed);
}

char *aspas(char *str)
{
	if (!str)
		return (NULL);
	char *final_str = remove_it(str, '"');
	return (final_str);
}