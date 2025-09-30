/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:46:11 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/29 21:38:04 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_matrix(char **matrix)
{
	int	ind;

	ind = -1;
	if (!matrix)
		return ; //VINI ADDED THIS CHECK 
	while (matrix[++ind])
		free(matrix[ind]);
	free (matrix);
}
