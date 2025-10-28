/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:18:05 by jlima-so          #+#    #+#             */
/*   Updated: 2025/10/28 15:20:04 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

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
