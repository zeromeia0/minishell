/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:57:38 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 16:57:43 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	simple_syntax(char **mat)
{
	if (ft_strcmp(*mat, "(") == 0)
	{
		while (ft_strcmp(*mat, ")"))
			mat++;
		syntax_error_msg(*(mat + 1));
		return (1);
	}
	while (*mat && ft_strcmp(*mat, "("))
		mat++;
	if (*mat)
	{
		syntax_error_msg(*(mat + 1));
		return (1);
	}
	return (0);
}
