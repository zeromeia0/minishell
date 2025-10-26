/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:24:06 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/26 15:27:38 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void remove_aspas(char *dest, const char *src)
{
    int start = 0;
    int end = ft_strlen(src) - 1;
    if ((src[start] == '"' && src[end] == '"') || (src[start] == '\'' && src[end] == '\''))
    {
        start++;
        end--;
    }
    int j = 0;
    for (int i = start; i <= end; i++)
        dest[j++] = src[i];
    dest[j] = '\0';
}

char	*remove_it(char *str, int c)
{
	int		i;
	int		j;
	int		count;
	char	*removed;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	count = count_it(str, c);
	removed = malloc(ft_strlen(str) + 1 - count);
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

char	*odd_aspas(char *str, char c)
{
	int		count;
	char	*result;
	char	*input;
	char	*tmp;

	count = count_it(str, c);
	result = ft_strdup(str);
	while (count % 2 != 0)
	{
		input = readline("> ");
		if (!input)
			continue ;
		tmp = result;
		result = ft_strjoin(result, input);
		free(tmp);
		free(input);
		count = count_it(result, c);
	}
	return (result);
}

char	*aspas(char *str, int c)
{
	char	*with_closed_quotes;
	char	*cleaned;

	if (!str)
		return (NULL);
	with_closed_quotes = odd_aspas(str, c);
	cleaned = remove_it(with_closed_quotes, c);
	free(with_closed_quotes);
	return (cleaned);
}
