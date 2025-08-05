/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:19:15 by jlima-so          #+#    #+#             */
/*   Updated: 2025/08/05 17:44:48 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
while (str[ind] == '\t' || str[ind] == ' ' || str[ind] == '\n')
			ind++;
		if (ft_isminishell(str[ind]))
		{
			count++;
			while (ft_isminishell(str[ind]))
			{
				printf("%c", str[ind]);
				ind++;
			}
			printf(" is a word\n\n");
		}
		else if (str[ind] == '\'')
		{
			count++;
			ind++;
			while (str[ind] != '\'' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '\'')
				ind++;
			else
				return (-1 * '\'');
			printf(" is '\n\n");
		}
		else if (str[ind] == '\"')
		{
			count++;
			ind++;
			while (str[ind] != '\"' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '\"')
				ind++;
			else
				return (-1 * '\"');
			printf(" is \"\n\n");
		}
		else if (str[ind] == '`')
		{
			count++;
			ind++;
			while (str[ind] != '`' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '`')
				ind++;
			else
				return (-1 * '`');
			printf("is `\n\n");
		}
		else if (str[ind] == '[')
		{
			count++;
			ind++;
			while (str[ind] != ']' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == ']')
				ind++;
			else
				return (-1 * ']');
			printf(" is '\n\n");
		}
		else if (str[ind] == '{')
		{
			count++;
			ind++;
			while (str[ind] != '}' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '}')
				ind++;
			else
				return (-1 * '}');
			printf(" is '\n\n");
		}
		else if (str[ind] == '$')
		{
			count++;
			if (str[ind + 1] == '{')
			{
				while (str[ind] != '}' && str[ind])
				{
					printf("%c", str[ind]);
					ind++;
				}
				if (str[ind] == '}')
				{
					printf("%c is a variable\n\n", str[ind]);
					ind++;
				}
				else
					return (-1 * '}');
			}
			else
			{
				while ((str[ind] != ' ' && str[ind] != '\t') && str[ind])
				{
					printf("%c", str[ind]);
					ind++;
				}
				printf("%c is a variable\n\n", str[ind]);
				while ((str[ind] == ' ' || str[ind] == '\t') && str[ind])
					ind++;
			}
		}
		else
		{
			tokind = 0;
			while (tokens[tokind] && ft_strnstr(str + ind, tokens[tokind], 2) == NULL)
				tokind++;
			if (ft_strnstr(str + ind, tokens[tokind], 2))
			{
				write(1, str + ind, ft_strlen(tokens[tokind]));
				printf(" is %s\n\n", tokens[tokind]);
				ind += ft_strlen(tokens[tokind]);
				count++;
			}
			else if (str[ind])
				ind++;
		}
	if (str[ind] == '\0')
		return (count);
*/

#include "../minishell.h"

int	word_count(char *str, char **stokens, char **mtokens)
{
	int		ind;
	int		count;
	char	*sep_found;
	char	*sep[] = {"'", "\"", "`", NULL};

	ind  = 0;
	count = 0;
	while (str[ind])
	{
		while (str[ind] == ' ' || str[ind] == '\t')
			ind++;
		if (str[ind] == '\0')
			return (count);
		if (ft_strnmat(mtokens, str + ind, 2))
		{
			count++;
			write(1, str + ind, 2);
			write(1, "\n", 1);
			ind += 2;
		}
		else if (ft_strnmat(stokens, str + ind, 1))
		{
			count++;
			write(1, str + ind, 1);
			write(1, "\n", 1);
			ind++;
		}
		if ((ft_strnmat(mtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t'))
		{
			count++;
			while ((ft_strnmat(mtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
				&& str[ind] && (str[ind] != ' ' && str[ind] != '\t'))
			{
				sep_found = ft_strnmat(sep, str + ind, 1);
				if (sep_found)
				{
					while (str[ind] != *sep_found && str[ind])
					{
						write(1, str + ind, 1);
						ind++;
					}
					if (str[ind] == '\0')
						return (-(*sep_found));
					write(1, str + ind, 1);
					ind++;
				}
				else
				{
					write(1, str + ind, 1);
					ind++;
				}
			}
			write(1, "\n", 1);
		}
	}
	return (count);
}


char **tokenization(char *str)
{
	// int		ind;
	int		wc;
	char	*stokens[] = {">", "<", "&", "|", NULL};
	char	*mtokens[] = {"<>", ">>", "<<", "&>", ">&", NULL};

	wc = word_count(str, stokens, mtokens);

	if (wc < 0)
	{
		printf("\nUnclosed |%c|\n", -wc);

		return (NULL);
	}
	printf("\nwords in the input ->|%d|\n", wc);
	// ind = -1;
	// while (str[++ind])
	// {
		// 
	// }
	return (NULL);
}

char **parsing(void)
{
	char *str;
	char **mat;


	str = readline("------------------------------------\nminishell$ ");
	mat = tokenization(str);
	mat = &str;
	return (mat);
}