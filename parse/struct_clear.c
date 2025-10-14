/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:56:30 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 10:56:32 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

void	binary_clear(t_binary *binary)
{
	if (binary == NULL)
		return ;
	binary_clear(binary->left);
	binary->left = NULL;
	binary_clear(binary->right);
	binary->right = NULL;
	binary_clear(binary->subshell);
	binary->subshell = NULL;
	cmds_clear(binary->cmds);
	binary->cmds = NULL;
	free (binary->logic);
	binary->logic = NULL;
	free (binary->print_cmd);
	binary->print_cmd = NULL;
	if (binary->up)
	{
		free(binary);
		binary = NULL;
	}
	else
	{
		free(btree()->mat);
		btree()->mat = NULL;
	}
}

void	cmds_clear(t_cmds *cmds)
{
	if (cmds == NULL)
		return ;
	cmds_clear(cmds->next);
	cmds->next = NULL;
	outfile_clear(cmds->outfiles);
	cmds->outfiles = NULL;
	infile_clear(cmds->infiles);
	cmds->infiles = NULL;
	if (cmds->expanded)
	{
		free_matrix(cmds->cmd);
		cmds->cmd = NULL;
	}
	else
		free_matrix_nodes(cmds->cmd);
	free(cmds);
	cmds = NULL;
}

void	infile_clear(t_infile *infile)
{
	if (infile == NULL)
		return ;
	infile_clear(infile->next);
	infile->next = NULL;
	free(infile->file);
	infile->file = NULL;
	free(infile->token);
	infile->token = NULL;
	free(infile);
	infile = NULL;
}

void	outfile_clear(t_outfile *outfile)
{
	if (outfile == NULL)
		return ;
	outfile_clear(outfile->next);
	outfile->next = NULL;
	free(outfile->file);
	outfile->file = NULL;
	free(outfile->token);
	outfile->token = NULL;
	free(outfile);
	outfile = NULL;
}

void	wild_clear(t_wild *node)
{
	if (node == NULL)
		return ;
	wild_clear(node->next);
	free(node);
}
