
#include "../sigma_minishell.h"

int	separator_comp(char **mat, int flag)
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

int	input_comp(char *str)
{
	if (strncmp(str, "<<", 3) && strncmp(str, "<", 2))
		return (1);
	return (0);
}

int	output_comp(char *str)
{
	if (strncmp(str, ">>", 3) && strncmp(str, ">", 2))
		return (1);
	return (0);
}
/*
int	output_comp(char *str)
{
	if (strncmp(str, ">>", 3) == 0 || strncmp(str, "&>", 3) == 0\
		|| strncmp(str, "0>", 3) == 0 || strncmp(str, "1>", 3) == 0\
			|| strncmp(str, "2>", 3) == 0 || strncmp(str, ">&", 3) == 0)
					return (0);
	if (strncmp(str, "0<>", 4) == 0 || strncmp(str, "1<>", 4) == 0 \
		|| strncmp(str, "&>>", 4) == 0 || strncmp(str, "0>>", 4) == 0\
			|| strncmp(str, "1>>", 4) == 0 || strncmp(str, "2>>", 4) == 0\
				|| strncmp(str, "2<>", 4) == 0)\
						return (0);
	return (1);
}
int	input_comp(char *str)
{
	if (strncmp(str, "<<", 3) && strncmp(str, "<>", 3) && strncmp(str, "<", 2))
		return (1);
	return (0);
}
*/

t_infile	*get_infile(char **mat)
{
	t_infile	*infile;
	int			ind; 

	ind = 0;
	if (mat == NULL)
		return (NULL);
	while (mat[ind] && input_comp(mat[ind]))
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

int redirect_comp(char *str)
{
	if (strncmp(str, "0>&1", 5) == 0 || strncmp(str, "1>&0", 5) == 0\
		|| strncmp(str, "2>&0", 5) == 0 || strncmp(str, "1>&2", 5) == 0\
			|| strncmp(str, "2>&1", 5) == 0 || strncmp(str, "0>&2", 5) == 0)
					return (0);
	return (1);
}

// output is:
	// ">>", "&>", ">&", "0>", "1>", "2>"
	// "0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
	// "0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

// input is:
// 	"<<", "<", "<>"
t_outfile	*get_outfile(char **mat)
{
	t_outfile	*outfile;
	int			flag;
	int			ind;

	ind = 0;
	if (mat == NULL)
		return (NULL);
	while (mat[ind] && ft_strncmp(mat[ind], "|", 2)
		&& (output_comp(mat[ind]) && redirect_comp(mat[ind])))
		ind++;
	if (mat[ind] == NULL || ft_strncmp(mat[ind], "|", 2) == 0)
		return (NULL);
	flag = redirect_comp(mat[ind]);
	if (flag)
		outfile = outfile_new(mat[ind + 1], mat[ind]);
	else
		outfile = outfile_new(NULL, mat[ind]);
	if (outfile == NULL)
		return (NULL);
	mat[ind] = NULL;
	if (flag)
		mat[ind + 1] = NULL;
	ft_matrix_unify(mat + ind, mat + ind + 1 + flag);
	outfile->next = get_outfile (mat + ind);
	return (outfile);
}

int	find_pipe(char **mat)
{
	int ind;

	ind = 0;
	while (mat[ind] && ft_strncmp(mat[ind], "&", 2))
		ind++;
	return ((mat[ind] == NULL) * -1 + (mat[ind] != NULL) * ind);
}

t_cmds	*get_cmds(char **mat)
{
	t_cmds	*cmds;
	int		sep;

	if (mat == NULL || *mat == NULL)
		return (NULL);
	sep = find_pipe(mat);
	if (sep != -1)
	{
		free(mat[sep]);
		mat[sep] = NULL;
	}
	cmds = cmds_new(mat, get_outfile(mat));
	if (sep != -1)
		cmds->next = get_cmds(mat + sep + 1);
	return (cmds);
}
// in < cat | cat & echo done & echo ola
// in < cat | cat & echo done &

void	create_binary_tree(char **mat, int	shlvl, t_binary *tree)
{
	int	sub;

	sub = separator_comp(mat, 0);
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

	sep = separator_comp(mat, 1);
	if (sep == 0)
	{
		tree->table = table_new(get_infile(mat), get_cmds(mat));
		// return (get_cmds(mat, tree));
		return ;
	}
	tree->left = binary_new(id ,EMPTY, tree, NULL);
	if (tree->left == NULL)
	{
		btree()->type = ERROR;
		return ;
	}
	tree->right = binary_new(id ,EMPTY, tree, NULL);
	if (tree->right == NULL)
	{
		btree()->type = ERROR;
		return ;
	}
	free (mat[sep]);
	mat[sep] = NULL;
	create_binary_lvl (mat + sep + 1, 1, tree->right);
	create_binary_lvl (mat, 1, tree->left);
}
