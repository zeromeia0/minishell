
#include "../minishell.h"

int	find_separator(char **mat, int flag)
{
	int	ind;

	ind = ft_matlen(mat);
	if (flag == 1)
	{
		while (--ind >= 0)
			if (ft_strncmp(mat[ind], "&&", 3) || ft_strncmp(mat[ind], "||", 3))
				return (ind);
	}
	else
	{
		while (--ind >= 0)
			if (ft_strncmp(mat[ind], "&", 2))
				return (ind);
	}
	return (0);
}

// void	create_table(char **mat, t_binary *tree)
// {
	// int			sub;
	// t_cmds		*cmds;
	// t_outfile	*outfile;
// 
	// cmds = NULL;
	// outfile = NULL;
	// sub = find_separator(mat, 0);
	// if (sub)
	// {
		// free (mat[sub]);
		// mat[sub] = NULL;
		// create_binary_tree (mat, 1, tree->subshell);
		// tree->subshell = binary_new(EMPTY, tree, NULL);
		// create_binary_tree(mat, 1, tree->subshell);
// 
		// outfile = find_outfile(mat + sub + 1);
		// cmds_new(mat + sub + 1, );
	// }
// }
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
