/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_unify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:18:14 by jlima-so          #+#    #+#             */
/*   Updated: 2025/08/10 20:12:39 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_matrix_unify(char **dest, char **src)
{
	if (src == NULL || dest == NULL)
		return;
	while (*src != NULL)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = *src;
}
