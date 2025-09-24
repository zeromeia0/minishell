/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:03:11 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 18:09:25 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	get_total(char **mat, int indv, int total)
{
	int	indh;

	while (mat[indv])
	{
		indh = 0;
		while (mat[indv][indh])
			indh++;
		total += indh + 1;
		indv++;
	}
	return (total);
}

char	*ft_join_matrix(char **mat, int indv, int ind, int total)
{
	char	*ret;
	int		indh;

	total = get_total(mat, indv, total);
	ret = ft_calloc(total, sizeof(char));
	if (ret == NULL)
		return (NULL);
	ind = 0;
	indv = -1;
	while (mat[++indv])
	{
		indh = 0;
		while (mat[indv][indh])
		{
			ret[ind] = mat[indv][indh];
			indh++;
			ind++;
		}
		if (mat[indv + 1] != NULL && mat[indv + 1][0] != '\0')
		{
			ret[ind] = ' ';
			ind++;
		}
	}
	return (ret);
}
