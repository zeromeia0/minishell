/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_expre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:04:31 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/07 21:04:37 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	truth_value(char **s, int *count, int ind, char ch)
{
	return (((*s + *count)[ind] != '\0' && ((*s + *count)[ind] != '$'))
		|| (ch == '\'' && (*s + *count)[ind] == '$')
			|| ((*s + *count)[ind] == '$' && !ft_isalnum((*s + *count)[ind + 1])
			&& (*s + *count)[ind + 1] != '?' && (*s + *count)[ind + 1] != '_'));
}

int	verify_value(char *str, int count)
{
	return ((str[count] != '\0' && str[count] != '$')
				|| (str[count] == '$' && !ft_isalnum(str[count + 1])
					&& str[count + 1] != '?' && str[count + 1] != '_'));
}