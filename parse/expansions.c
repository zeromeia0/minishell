/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:35:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/28 18:27:05 by jlima-so         ###   ########.fr       */
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

int	truth_value(char **s, int *count, int ind, char ch)
{
	return (((*s + *count)[ind] != '\0' && ((*s + *count)[ind] != '$'))
		|| (ch == '\'' && (*s + *count)[ind] == '$')
			|| ((*s + *count)[ind] == '$' && !ft_isalnum((*s + *count)[ind + 1])
			&& (*s + *count)[ind + 1] != '?' && (*s + *count)[ind + 1] != '_'));
}

void	quote_aux(char **s, int *count, char **str2, int ind)
{
	int		value;
	char	ch;

	ch = (*s + *count)[0];
	while ((*s + *count)[ind] != '\0' && (*s + *count)[ind] != ch)
	{
		if (ch == '\"')
		{
			*s = single_expand(*s, *count + ind, 0);
			if (*(*s + 2) == '\0')
				break ;
			value = get_diff(*s + ind + *count, *str2 + ind + *count, 0);
			ind += value - (value != 0);
			free(*str2);
			*str2 = ft_strdup(*s);
		}
		printf("%s |%d %d|", *s, *count, ind);
		ind += truth_value(s, count, ind, ch);
	}
	*(*s + *count + ind) = '\n';
	*(*s + *count) = '\n';
	free(*str2);
	*str2 = ft_strdup(*s);
	*count += ind;
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
				|| (str[count] == '$' && !ft_isalnum(str[count + 1])
					&& str[count + 1] != '?' && str[count + 1] != '_');
	}
	free(str2);
	printf("->|%s|\n", str);
	fflush(stdout);
	return (str);
}
