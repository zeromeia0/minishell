/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:35:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/24 14:18:49 by jlima-so         ###   ########.fr       */
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

void	quote_aux(char *str, int *count, char *str2)
{
	int		ind;
	char	ch;

	ind = 0;
	ch = (str + *count)[ind];
	ind++;
	while ((str + *count)[ind] != '\0' && (str + *count)[ind] != ch)
	{
		if (ch == '\"')
		{
			str = single_expand(str, *count + ind, 0);
			if (ft_strcmp(str, str2))
			{
				ind += get_diff(str, str2, 0);
				free(str2);
				str2 = ft_strdup(str);
			}
		}
		ind += ((str + *count)[ind] != '\0');
	}
	ft_memmove((str + *count) + ind, (str + *count) + ind + 1,
		ft_strlen((str + *count) + ind));
	ft_memmove((str + *count), (str + *count) + 1, ft_strlen((str + *count)));
	*count += ind - 1;
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
		if (ft_strcmp(str, str2))
		{
			count += get_diff(str + count, str2 + count + 2, 0);
			free(str2);
			str2 = ft_strdup(str + count);
		}
		if (*(str + count) == '\"' || *(str + count) == '\'')
			quote_aux(str, &count, str2);
		else
			count += (str[count] != '\0');
	}
	if (str2)
		free(str2);
	return (str);
}
