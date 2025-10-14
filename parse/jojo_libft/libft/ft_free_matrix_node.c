/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:00:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/10/09 10:05:32 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_matrix_nodes(char **mat)
{
	int	ind;

	if (mat == NULL)
		return ;
	ind = -1;
	while (mat[++ind])
		free(mat[ind]);
	*mat = NULL;
}
