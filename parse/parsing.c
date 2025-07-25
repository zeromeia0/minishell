/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:19:15 by jlima-so          #+#    #+#             */
/*   Updated: 2025/07/25 16:59:58 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_count(char *str, char **tokens)
{
	int		ind;
	int		tokind;
	int		count;

	ind  = 0;
	count = 0;
	while (str[ind])
	{
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
	}
	return (count);
}

char **tokenization(char *str)
{
	// int		ind;
	int		wc;
	char	*tokens[] = {/* "||", "&&",  */"<>", ">>", "<<", "&>", ">&", ">", "<", "&", "|", NULL};

	wc = word_count(str, tokens);

	if (wc < 0)
	{
		printf("Unclosed '%c'\n", -wc);

		return (NULL);
	}
	printf("words in the input ->|%d|\n", wc);
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