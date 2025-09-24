/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:56:20 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 19:00:25 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

int	find_tokens(char *str, t_token tokens)
{
	if (ft_matnstr(tokens.dtokens, str, 2))
		return (2);
	if (ft_matnstr(tokens.stokens, str, 1))
		return (1);
	return (0);
}

static int	word_count_aux(int ind, char *str, t_token tokens, char **sep)
{
	char	*sep_found;

	while (find_tokens(str + ind, tokens) == 0 && str[ind]
		&& (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		sep_found = ft_matnstr(sep, str + ind, 1);
		if (sep_found && ++ind)
		{
			while (str[ind] != *sep_found && str[ind])
				ind++;
			if (str[ind] == '\0')
				return (-(*sep_found));
			ind++;
		}
		else
			ind++;
	}
	return (ind);
}

int	word_count(char *str, t_token tokens, char **sep)
{
	int		i;
	int		cnt;
	int		token_found;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] == '\0')
			return (cnt);
		token_found = find_tokens(str + i, tokens);
		if (token_found)
		{
			cnt++;
			i += token_found;
		}
		else if (find_tokens(str + i, tokens) == 0 && str[i]
			&& (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') && ++cnt)
			i = word_count_aux(i, str, tokens, sep);
		if (i < 0)
			return (i);
	}
	return (cnt);
}

// echo $USER "$USER" '$USER' "'$USER'" '"$USER"'
int	parsing_strlen_aux(int ind, char *str, t_token tokens, char **sep)
{
	char	*sep_found;

	while (find_tokens(str + ind, tokens) == 0 && str[ind]
		&& (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		sep_found = ft_matnstr(sep, str + ind, 1);
		if (sep_found)
		{
			ind++;
			while (str[ind] != *sep_found && str[ind])
				ind++;
			if (str[ind] == '\0')
			{
				printf("we found the error\n");
				fflush(stdout);
				return (-(*sep_found));
			}
			ind++;
		}
		else
			ind++;
	}
	return (ind);
}

int	parsing_strlen(char *str, t_token tokens, char **sep)
{
	int	ind;
	int	token_found;

	ind = 0;
	token_found = find_tokens(str + ind, tokens);
	if (token_found)
		return (token_found);
	else if (find_tokens(str + ind, tokens) == 0 && str[ind]
		&& (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		return (parsing_strlen_aux(ind, str, tokens, sep));
	return (0);
}
