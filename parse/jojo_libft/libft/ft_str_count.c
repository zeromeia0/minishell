/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:13:20 by jlima-so          #+#    #+#             */
/*   Updated: 2025/10/09 09:36:52 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_str_count(char *str, char c)
{
	int	ind;
	int	count;

	count = 0;
	ind = 0;
	while (str[ind])
	{
		if (str[ind] != c && (str[ind + 1] == '\0'
				|| str[ind + 1] == c))
			count++;
		ind++;
	}
	return (count);
}
