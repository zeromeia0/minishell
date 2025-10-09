/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmrep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 09:45:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 09:45:36 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_rmrep(char *str, char rep)
{
	int	ind;

	if (str == NULL || *str == '\0')
		return (str);
	ind = 1;
	while (str[ind])
	{
		if (str[ind] == rep && str[ind - 1] == rep)
			ft_memmove(str + ind - 1, str + ind, ft_strlen(str + ind) + 1);
		else
			ind++;
	}
	return (str);
}
