/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:35:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/27 15:30:30 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	get_diff(char *str1, char *str2, int start)
{
	int	ind1;
	int	ind2;

	while (str1[start] && str1[start] == str2[start])
		start++;
	ind1 = ft_strlen(str1);
	ind2 = ft_strlen(str2);
	while (ind1 > start && ind2 > start && str1[ind1] == str2[ind2])
	{
		ind1--;
		ind2--;
	}
	return (ind1 - start);
}

char	*expand_hd(char *str)
{
	char	*str2;
	int		count;

	str2 = ft_strdup(str);
	count = -1;
	while (str[++count])
	{
		str = single_expand(str, count, 0);
		if (str == NULL || *str == '\0')
			return (free(str2), str);
		if (ft_strcmp(str, str2))
		{
			count += get_diff(str, str2, 0);
			free(str2);
			str2 = ft_strdup(str);
		}
	}
	free(str2);
	return (str);
}

void	rm_quote(char *dest, char *src)
{
	char	ch;
	int		beg;
	int		end;

	dest = ft_strcpy(dest, src);
	beg = 0;
	ch = 0;
	while (dest[beg] && beg < 4095)
	{
		if (dest[beg] == '\'' || dest[beg] == '\"')
		{
			ch = dest[beg];
			end = beg + 1;
			while (dest[end] != '\0' && dest[end] != ch && end < 4094)
				end++;
			ft_memmove(dest + end, dest + end + 1, ft_strlen(dest + end));
			ft_memmove(dest + beg, dest + beg + 1, ft_strlen(dest));
			beg = end - 1;
		}
		else
			beg++;
	}
}

void	quote_aux(char **s, int *c, char **str2, int i)
{
	char	ch;
	int		value;

	ch = (*s + *c)[0];
	while ((*s + *c)[i] != '\0' && (*s + *c)[i] != ch)
	{
		if (ch == '\"')
		{
			*s = single_expand(*s, *c + i, 0);
			if (*(*s + 2) == '\0')
				break ;
			value = get_diff(*s + i + *c, *str2 + i + *c, 0);
			i += value - (value != 0);
			free(*str2);
			*str2 = ft_strdup(*s);
		}
		i += (((*s + *c)[i] != '\0' && ((*s + *c)[i] != '$' || ch == '\'')))
				|| ((*s + *c)[i] == '$' && ft_isalnum((*s + *c)[i + 1]) == 0);
	}
	ft_memmove((*s + *c) + i, (*s + *c) + i + 1,
		ft_strlen((*s + *c) + i));
	ft_memmove((*s + *c), (*s + *c) + 1, ft_strlen((*s + *c)));
	free(*str2);
	*str2 = ft_strdup(*s);
	*c += (ft_strcmp(*s, *str2) == 0) * (i - 1);
}

char	*quote(char *str)
{
	char	*str2;
	int		count;

	str2 = ft_strdup(str);
	count = 0;
	while (str[count])
	{
		str = single_expand(str, count, 0);
		if (str == NULL || *str == '\0')
			return (free(str2), str);
		if (ft_strcmp(str, str2))
		{
			count += get_diff(str + count, str2 + count + 1, 0);
			free(str2);
			str2 = ft_strdup(str);
		}
		if (*(str + count) == '\"' || *(str + count) == '\'')
			quote_aux(&str, &count, &str2, 1);
		else
			count += (str[count] != '\0' && str[count] != '$')
				|| (str[count] == '$' && ft_isalnum(str[count + 1]) == 0);
	}
	if (str2)
		free(str2);
	return (str);
}
