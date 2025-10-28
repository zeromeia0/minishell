/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:50:26 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/28 00:15:09 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

void	expand_args(t_cmds *cmd)
{
	char	**mat;
	char	**temp;
	int		ind;

	if (!cmd)
		return ;
	temp = cmd->cmd;
	mat = wildcards(temp, 0, 0);
	cmd->expanded = (temp != mat);
	if (temp != mat)
		free_matrix_nodes(temp);
	else
	{
		ind = -1;
		while (mat[++ind])
			mat[ind] = quote(mat[ind]);
	}
	cmd->cmd = mat;
	expand_infiles(cmd->infiles);
	expand_outfiles(cmd->outfiles);
	cmd->cmd = expand_matrix(cmd);
	expand_args(cmd->next);
}

void	take_quotes(char *str)
{
	char	ch;
	int		ind;

	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			ind = 0;
			ch = str[ind];
			ind++;
			while (str[ind] != ch)
				ind++;
			ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind));
			ft_memmove(str, str + 1, ft_strlen(str));
			str += ind - 1;
		}
		else
			str++;
	}
}

void	expand_infiles(t_infile *infile)
{
	int		len;
	char	*temp;

	if (!infile || !infile->file)
		return ;
	if (ft_strcmp(infile->token, "<<"))
	{
		len = ft_strlen(infile->file);
		infile->flag = 0;
		take_quotes(infile->file);
		if (len != (int)ft_strlen(infile->file))
			infile->flag = 1;
	}
	else
	{
		infile->file = quote(infile->file);
		if (ft_strchr(infile->file, '\n'))
		{
			temp = infile->file;
			infile->file = ft_strsubs(temp, '\n', ' ');
			free(temp);
		}
	}
	expand_infiles(infile->next);
}

void	expand_outfiles(t_outfile *outfile)
{
	char	*temp;

	if (!outfile || !outfile->file)
		return ;
	outfile->file = quote(outfile->file);
	if (ft_strchr(outfile->file, '\n'))
	{
		temp = outfile->file;
		outfile->file = ft_strsubs(temp, '\n', ' ');
		free(temp);
	}
	expand_outfiles(outfile->next);
}

char	*helper_add_quotes_export(char *new_str, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		new_str[j++] = str[i++];
	if (str[i] == '=')
	{
		new_str[j++] = str[i++];
		new_str[j++] = '"';
	}
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j++] = '"';
	new_str[j] = '\0';
	return (new_str);
}
