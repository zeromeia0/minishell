/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:21:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/09/24 18:19:08 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_matrix(char **matrix)
{
	int	indv;
	int	indh;

	if (matrix == NULL)
		return ;
	indv = -1;
	while (matrix[++indv])
	{
		indh = -1;
		while (matrix[indv][++indh])
			write(2, &matrix[indv][indh], 1);
		write(2, "\n", 1);
	}
}
