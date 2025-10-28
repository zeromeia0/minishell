/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:50:55 by jlima-so          #+#    #+#             */
/*   Updated: 2025/10/28 00:01:01 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	word_count1(char *str, char c, char sep)
{
	int		wc;

	wc = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str && *str != c)
		{
			wc++;
			while (*str && *str != c)
			{
				if (*str == sep)
					str = ft_strchr(str + 1, sep) + 1;
				while (*str && *str != c && *str != sep)
					str++;
			}
		}
	}
	return (wc);
}

int	ft_split_sep_aux(char *str, char c, char sep)
{
	int	ind;

	ind = 0;
	while (str[ind] && str[ind] != c)
	{
		if (str[ind] == sep)
		{
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
			ind += ft_strchr(str + ind + 1, sep) - (str + ind);
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
		}
		while (str[ind] && str[ind] != sep && str[ind] != c)
			ind++;
	}
	return (ind);
}

char	**ft_split_sep(char *str, char c, char sep)
{
	char	**ret;	
	int		wc;
	int		ind;
	int		loop;

	wc = word_count1(str, c, sep);
	ret = malloc((wc + 1) * sizeof(char *));
	ret[wc] = NULL;
	loop = -1;
	while (++loop < wc)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			return (ret);
		ind = ft_split_sep_aux(str, c, sep);
		ret[loop] = ft_strndup(str, ind);
		str += ind;
	}
	return (ret);
}
