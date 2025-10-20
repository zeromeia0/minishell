/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:28:12 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/20 13:40:45 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsubs(char *str, char ch1, char ch2)
{
	int		ind;
	char	*ret;

	ind = ft_strlen(str);
	ret = malloc(ind + 1);
	if (ret == NULL)
		return (NULL);
	ret[ind] = '\0';
	ind = -1;
	while (str[++ind])
	{
		if (str[ind] == ch1)
			ret[ind] = ch2;
		else
			ret[ind] = str[ind];
	}
	return (ret);
}
