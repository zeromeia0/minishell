/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_giga_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:50:55 by jlima-so          #+#    #+#             */
/*   Updated: 2025/10/09 09:58:20 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**ft_giga_split_aux(char *str, int count, int i, char c);

static int	close_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] != quote)
		i++;
	i++;
	return (i);
}

char	*ft_strndup(char *str, int ind)
{
	char	*ret;

	if (str == NULL)
		return (NULL);
	ret = ft_calloc (ind + 1, 1);
	while (ind--)
		ret[ind] = str[ind];
	return (ret);
}

static char	**end_loop(char *str, int i, int count, char c)
{
	char	**ret;
	char	**mat;

	ret = ft_giga_split_aux(str + i, count + 1, -1, c);
	if (ret == NULL)
		return (NULL);
	ret[count] = ft_strndup(str, i);
	if (ret[count] == NULL)
	{
		mat = ret + count + 1;
		while (*mat != NULL)
		{
			free(*mat);
			mat++;
		}
		return (free(ret), NULL);
	}
	return (ret);
}

static char	**ft_giga_split_aux(char *str, int count, int i, char c)
{
	char	**ret;

	while (*str && *str == c)
		str++;
	if (*str == '\0')
	{
		ret = malloc(sizeof(char *) * (count + 1));
		if (ret == NULL)
			return (NULL);
		ret[count] = NULL;
		return (ret);
	}
	while (str[++i])
	{
		while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i = close_quotes(str, i);
		if (str[i] == c || str[i] == '\0')
			return (end_loop(str, i, count, c));
	}
	return (NULL);
}

char	**ft_giga_split(char *str, char c)
{
	if (str == NULL)
		return (NULL);
	return (ft_giga_split_aux(str, 0, -1, c));
}
