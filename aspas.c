#include "sigma_minishell.h"

char *aspas(char *str)
{
	int i;
	int j;
	int	count;
	char *new_str;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(str, '"'))
			count++;
		i++;
	}
	new_str = malloc(i + 1);
	if (!new_str)
		return (NULL);
	j = 0;
		if (count % 2 == 1)
	{
		while (j < i)
		{
			if (str[j] == '"')
				j++;
			new_str[j] = str[j];
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

int main(void)
{
	char str[] = "salve rapazeada";
	printf("%s", str);
	return (0);
}