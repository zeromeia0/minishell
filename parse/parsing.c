/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:21:30 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/26 16:51:52 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

char	**tokenization(char *str, t_token tokens, char **sep, int wc)
{
	int		ind;
	int		strcount;
	char	**ret;

	if (wc < 0)
		return (single_error_msg(-wc), NULL);
	ret = malloc(sizeof(char *) * (wc + 1));
	if (ret == NULL)
		return (NULL);
	ret[wc] = NULL;
	ind = -1;
	while (++ind < wc)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str == '\0')
			break ;
		strcount = parsing_strlen(str, tokens, sep);
		ret[ind] = ft_strndup(str, strcount);
		if (ret[ind] == NULL)
			return (ft_free_matrix(ret), NULL);
		str += strcount;
	}
	return (ret);
}

void	init_tree(char	**mat)
{
	btree()->sublvl = 0;
	btree()->type = EMPTY;
	btree()->left_ret = -1;
	btree()->right_ret = -1;
	btree()->subshell_ret = -1;
	btree()->cmds = NULL;
	btree()->up = NULL;
	btree()->left = NULL;
	btree()->right = NULL;
	btree()->subshell = NULL;
	btree()->global_signal = 0;
	btree()->logic = NULL;
	btree()->print_cmd = NULL;
	btree()->mat = mat;
}

int	sep_count(char **mat)
{
	int	count;

	count = 0;
	while (*mat)
	{
		if (ft_strncmp(*mat, "&", 2) == 0)
			count++;
		mat++;
	}
	return (count);
}

void	init_tokens(t_token *tokens)
{
	static char	*stokens[7];
	static char	*dtokens[5];
	static char	*sep[4];

	stokens[0] = "(";
	stokens[1] = ")";
	stokens[2] = "&";
	stokens[3] = "|";
	stokens[4] = ">";
	stokens[5] = "<";
	stokens[6] = NULL;
	dtokens[0] = "||";
	dtokens[1] = "&&";
	dtokens[2] = ">>";
	dtokens[3] = "<<";
	dtokens[4] = NULL;
	sep[0] = "'";
	sep[1] = "\"";
	sep[2] = "`";
	sep[3] = NULL;
	tokens->dtokens = dtokens;
	tokens->stokens = stokens;
	tokens->sep = sep;
}

void	rm_quote(char *dest, char *src)
{
	char	ch;
	int		beg;
	int		end;

	dest = ft_strcpy(dest, src);
	beg = 0;
	ch = 0;
	while (dest[beg] && beg < 4095)
	{
		if (dest[beg] == '\'' || dest[beg] == '\"')
		{
			ch = dest[beg];
			end = beg + 1;
			while (dest[end] != '\0' && dest[end] != ch && end < 4094)
				end++;
			printf("from->%s\nto->%s\n", dest + beg, dest + beg + 1);
			printf("from->%s\nto->%s\n\n", dest + end, dest + end + 1);
			ft_memmove(dest + end, dest + end + 1, ft_strlen(dest + end));
			ft_memmove(dest + beg, dest + beg + 1, ft_strlen(dest));
			beg = end - 1;
		}
		else
			beg++;
	}
}

int	parsing(char *str)
{
	char			**mat;
	static t_token	tokens;
	char			str1[4096];

	if (str == NULL || *str == '\0')
		return (1);
	if (tokens.dtokens == NULL)
		init_tokens(&tokens);
	mat = NULL;
	if (str != NULL && *str != '\0')
		mat = tokenization(str, tokens, tokens.sep,
				word_count(str, tokens, tokens.sep));
	if (mat == NULL)
		return (1);
	if (check_syntax(mat, tokens))
		return (1);
	init_tree(mat);
	create_binary_tree(mat, sep_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (1);
	return (0);
}
