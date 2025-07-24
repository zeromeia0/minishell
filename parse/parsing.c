/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:19:15 by jlima-so          #+#    #+#             */
/*   Updated: 2025/07/24 20:59:15 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* char **tokenization(char *str)
{
	int	ind;
	char **sep = {"||", "&&", " ", "\t", "<>", ">>", "<<", "&&", "&&", "&&", "&&", "&&", "&&", ">", "<", NULL};
	ind = -1;
	while (str[++ind])
	{
		
	}
} */

char **parsing(void)
{
	char *str;
	char **mat;
	
	str = readline("minishell$ ");
	// mat = tokenization(str);
	mat = &str;
	return (mat);
}