/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:28:12 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 10:13:21 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsubs(char *str, char ch1, char ch2)
{
	int		ind;
	char	*ret;

	ind = -1;
	ret = malloc(ft_strlen(str));
	if (ret == NULL)
		return (NULL);
	while (str[++ind])
	{
		if (str[ind] == ch1)
			ret[ind] = ch2;
		else
			ret[ind] = str[ind];
	}
	ret[ind] = '\0';
	return (ret);
}
