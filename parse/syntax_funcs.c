/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:44:55 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 19:05:23 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

void	syntax_error_msg(char *str)
{
	write(1, "syntax error near unexpected token: `", 38);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
}

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

void	single_error_msg(char wc)
{
	ft_putstr_fd("syntax error near unexpected token: `", 2);
	write(1, &wc, 1);
	ft_putstr_fd("'\n", 2);
}
