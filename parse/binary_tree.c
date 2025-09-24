/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:55:31 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 20:20:18 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

/* void	print_thiscmds(t_cmds *cmds)
{
	while (cmds)
	{
		printf( "=====================================\n");
		printf( "starts commands\n\n");
		ft_print_matrix(cmds->cmd);
		printf( "end commands\n\n");
		printf( "starts outfiles\n\n");
		print_files((t_infile *)cmds->outfiles);
		printf( "end outfiles\n");
		printf( "=====================================\n");
		cmds = cmds->next;
	}
}*/

int	separator_comp(char **mat, int flag, int ind, int pcount)
{
	if (flag == 1)
	{
		while (--ind >= 0)
		{
			if (ft_strncmp(mat[ind], ")", 2) == 0 && ++pcount && --ind >= 0)
			{
				while (ind >= 0 && pcount)
				{
					if (ft_strncmp(mat[ind], ")", 2) == 0)
						pcount++;
					if (ft_strncmp(mat[ind], "(", 2) == 0)
						pcount--;
					ind--;
				}
			}
			if (ind >= 0 && (ft_strncmp(mat[ind], "&&", 3) == 0
					|| ft_strncmp(mat[ind], "||", 3) == 0))
				return (ind);
		}
	}
	else if (--ind)
		while (ind-- > 0)
			if (ft_strncmp(mat[ind], "&", 2) == 0)
				return (ind);
	return (0);
}

t_cmds	*get_cmds(char **mat)
{
	t_cmds	*cmds;
	int		sep;

	if (*mat == NULL)
		return (NULL);
	if (simple_syntax(mat))
		return (free_matrix_nodes(mat), btree()->type = ERROR, NULL);
	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return (NULL);
	sep = find_pipe(mat);
	if (sep != -1)
	{
		free(mat[sep]);
		mat[sep] = NULL;
	}
	cmds = cmds_new(get_outfile(mat), get_infile(mat), mat);
	if (cmds == NULL)
		return (btree()->type = ERROR, NULL);
	if (sep != -1)
		cmds->next = get_cmds(mat + sep + 1);
	return (cmds);
}

void	create_binary_tree(char **mat, int shlvl, t_binary *tree)
{
	int	sub;

	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return ;
	sub = separator_comp(mat, 0, ft_matlen(mat), 0);
	if (sub)
	{
		free(mat[sub]);
		mat[sub] = NULL;
		tree->subshell = binary_new(shlvl - 1, EMPTY, tree, NULL);
		if (tree->subshell == NULL)
		{
			btree()->type = ERROR;
			return ;
		}
		create_binary_tree (mat, shlvl - 1, tree->subshell);
		if (btree()->type == ERROR)
			return ;
		mat += sub + 1;
	}
	create_binary_lvl(mat, shlvl, tree);
}

int	open_parethesis(char **mat)
{
	int	ind;
	int	pcount;

	ind = 0;
	pcount = 0;
	if (ft_strncmp(mat[ind], "(", 2) == 0)
	{
		pcount++;
		while (pcount && mat[++ind])
		{
			if (ft_strncmp(mat[ind], "(", 2) == 0)
				pcount++;
			if (ft_strncmp(mat[ind], ")", 2) == 0)
				pcount--;
		}
		if (pcount == 0 && mat[ind + 1] == NULL)
		{
			free (*mat);
			free (mat[ind]);
			*mat = NULL;
			mat[ind] = NULL;
			return (1);
		}
	}
	return (0);
}

void	*create_binary_lvl(char **mat, int id, t_binary *tree)
{
	int	sep;	

	if (btree()->type == ERROR || mat == NULL || *mat == NULL)
		return (NULL);
	while (open_parethesis(mat))
		mat += 1;
	if (btree()->type == ERROR)
		return (NULL);
	sep = separator_comp(mat, 1, ft_matlen(mat), 0);
	if (sep == 0)
	{
		tree->print_cmd = ft_join_matrix(mat, 0, 0, 0);
		if (tree->print_cmd == NULL)
			return (btree()->type = ERROR, free_matrix_nodes(mat), NULL);
		return (tree->cmds = get_cmds(mat), NULL);
	}
	tree->left = binary_new(id, EMPTY, tree, NULL);
	tree->right = binary_new(id, EMPTY, tree, NULL);
	if (tree->right == NULL || tree->left == NULL)
		return (btree()->type = ERROR, NULL);
	tree->logic = mat[sep];
	mat[sep] = NULL;
	create_binary_lvl (mat, 1, tree->left);
	return (create_binary_lvl (mat + sep + 1, 1, tree->right), NULL);
}
