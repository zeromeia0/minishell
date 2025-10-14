/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:26:26 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/09 09:44:50 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_join_matrix_aux(char **mat, char *ret)
{
	int	ind;
	int	indv;
	int	indh;

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

char	*ft_join_matrix(char **mat, int total)
{
	char	*ret;
	int		indh;
	int		indv;

	indv = 0;
	while (mat[indv])
	{
		indh = 0;
		while (mat[indv][indh])
			indh++;
		total += indh + 1;
		indv++;
	}
	ret = ft_calloc(total, sizeof(char));
	if (ret == NULL)
		return (NULL);
	return (ft_join_matrix_aux(mat, ret));
}
