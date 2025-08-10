
#include "../minishell.h"

int	find_separator(char **mat, int flag)
{
	int	ind;

	ind = ft_matlen(mat);
	if (flag == 1)
	{
		while (--ind >= 0)
			if (ft_strncmp(mat[ind], "&&", 3) == 0|| ft_strncmp(mat[ind], "||", 3) == 0)
				return (ind);
	}
	else
	{
		while (--ind >= 0)
			if (ft_strncmp(mat[ind], "&", 2) == 0)
				return (ind);
	}
	return (0);
}
// < in < in2 < in3
// < in < in2 <

// t_infile	*get_infile(char **mat)
// {
// 	t_infile	*infile;
// 	int			ind; 

// 	if (mat == NULL || *mat == NULL)
// 		return (NULL);
// 	ind = -1;
// 	while (mat[++ind])
// 	{
// 		if (strncmp(mat[ind], "<<", 3) == 0 || strncmp(mat[ind], "<", 2) == 0 )
// 		{
// 			infile = infile_new(mat[ind + 1], mat[ind]);
// 			if (infile == NULL)
// 				return (NULL);
// 			break;
// 		}
// 	}
// 	if (*mat == NULL)
// 		return (NULL);
// 	infile->next = get_infile (mat + ind);
// 	return (infile);
// }

t_infile	*get_infile(char **mat)
{
	t_infile	*infile;
	int			ind; 

	ind = 0;
	if (mat == NULL)
		return (NULL);
	while (mat[ind] && strncmp(mat[ind], "<<", 3) && strncmp(mat[ind], "<", 2)
		&& strncmp(mat[ind], "<>", 3))
		ind++;
	if (mat[ind] == NULL)
		return (NULL);
	infile = infile_new(mat[ind + 1], mat[ind]);
	if (infile == NULL)
		return (NULL);
	mat[ind] = NULL;
	mat[ind + 1] = NULL;
	ft_matrix_unify(mat + ind, mat + ind + 2);
	infile->next = get_infile (mat + ind);
	return (infile);
}
// output is:
// 	">>", "&>", ">&", "0>", "1>", "2>"
//	"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
//	"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

// input is:
// 	"<<", "<", "<>"

void	create_table(char **mat, t_binary *tree)
{
	t_cmds		*cmds;
	t_outfile	*outfile;
	t_infile	*infile;

	infile = get_infile(mat);
	outfile = get_outfile(mat);
	cmds	= cmds_new();

}
// in < cat | cat & echo done & echo ola
// in < cat | cat & echo done &

void	create_binary_tree(char **mat, int	shlvl, t_binary *tree)
{
	int	sub;

	sub = find_separator(mat, 0);
	if (sub)
	{
		free(mat[sub]);
		mat[sub] = NULL;
		tree->subshell = binary_new(shlvl - 1, EMPTY, tree, NULL);
		create_binary_tree (mat, shlvl - 1, tree->subshell);
		mat += sub + 1;
	}
	create_binary_lvl(mat, shlvl, tree);
}

void	create_binary_lvl(char **mat, int id, t_binary *tree)
{
	int			sep;
	t_binary	*tree_node;
	t_table		*table;

	sep = find_separator(mat, 1);
	if (sep == 0)
		return (create_table(mat, tree));
	tree->left = binary_new(id ,EMPTY, tree, NULL);
	if (tree->left == NULL)
		return (btree()->type = ERROR, NULL);
	tree->right = binary_new(id ,EMPTY, tree, NULL);
	if (tree->right == NULL)
		return (btree()->type = ERROR, NULL);
	free (mat[sep]);
	mat[sep] = NULL;
	create_binary_lvl (mat + sep + 1, 1, tree->right);
	create_binary_lvl (mat, 1, tree->left);
}
