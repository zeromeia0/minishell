/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:35:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/24 14:50:14 by jlima-so         ###   ########.fr       */
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
	if (ind1 > ind2)
		return (ind1 - start);
	return (ind2 - start);
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

void	quote_aux(char **s, int *count, char **str2)
{
	int		ind;
	char	ch;

	ch = (*s + *count)[0];
	ind = 1;
	while ((*s + *count)[ind] != '\0' && (*s + *count)[ind] != ch)
	{
		if (ch == '\"')
		{
			*s = single_expand(*s, *count + ind, 0);
			if (*(*s + 2) == '\0')
				break ;
			if (ft_strcmp(*s, *str2))
			{
				ind += get_diff(*s, *str2, 0);
				free(*str2);
				*str2 = ft_strdup(*s);
			}
		}
		ind += ((*s + *count)[ind] != '\0');
	}
	ft_memmove((*s + *count) + ind, (*s + *count) + ind + 1,
		ft_strlen((*s + *count) + ind));
	ft_memmove((*s + *count), (*s + *count) + 1, ft_strlen((*s + *count)));
	*count += (ft_strcmp(*s, *str2) == 0) * (ind - 2);
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
			count += get_diff(str + count, str2 + count + 2, 0);
			free(str2);
			str2 = ft_strdup(str);
		}
		if (*(str + count) == '\"' || *(str + count) == '\'')
			quote_aux(&str, &count, &str2);
		else
			count += (str[count] != '\0');
	}
	if (str2)
		free(str2);
	return (str);
}
