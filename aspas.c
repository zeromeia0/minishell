#include "my_libft/libft.h"
#include "sigma_minishell.h"


int count_it(char *str, int c)
{
	int i = 0;
	int count = 0;
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
	int count = count_it(str, c);
	char *removed = malloc(ft_strlen(str) + 1 - count);
	if (!removed)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			{
				str[i] = str[i + 1];
				i++;
			}
		removed[i] = str[i];
		i++;
	}
	return (removed);
}

char *aspas(char *str)
{
	char *new_str = malloc(ft_strlen(str) + 1 - count_it(str, '"'));
	remove_it(str, '"');
	ft_strcpy(new_str, str);
	return (new_str);
}

int main(void)
{
	char str[] = "sal\"ve r\"apaze\"ada\n";
	aspas(str);
	printf("%s", str);
	return (0);
}