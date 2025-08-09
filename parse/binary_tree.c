
#include "../minishell.h"

void	create_binary_tree(char **mat, int id, t_binary *tree)
{
	int			sep;
	t_binary	*tree_node;
	t_table		*table;

	sep = find_separator(mat);
	if (sep == 0)
		return (create_table(mat, tree));
	tree->left = create_tree_node();
	tree->right = create_tree_node();
	create_binary_tree (mat + sep + 1, 1, tree->right);
	free (mat[sep]);
	mat[sep] = NULL;
	create_binary_tree (mat, 1, tree->right);
	if (id == 0)
		free(mat);
}
