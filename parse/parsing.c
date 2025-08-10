#include "../minishell.h"

/* int	find_fd_red(char *str)
{
	int	ind;

	ind = 0;
	while(str[ind] >= '0' && str[ind] <= '9')
		ind++;
	if (str[ind] == '\0')
		return (0);
	if (str[ind] == '&')
	{
		
		ind++;
	}
	if (str[ind] == '>' && str[ind + 1] == '>')
		return (ind + 2);
	if (str[ind] == '>')
		return (ind + 1);
	return (0);
} */

int	find_tokens(char *str, t_token tokens)
{
	if (ft_strnmat(tokens.qtokens, str, 4))
		return (4);
	if (ft_strnmat(tokens.ttokens, str, 3))
		return (3);
	if (ft_strnmat(tokens.dtokens, str, 2))
		return (2);
	if (ft_strnmat(tokens.stokens, str, 1))
		return (1);
	return (0);
}

int	word_count(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		count;
	int		token_found;
	char	*sep_found;

	ind  = 0;
	count = 0;
	while (str[ind])
	{
		while (str[ind] == ' ' || str[ind] == '\t' || str[ind] == '\n')
			ind++;
		if (str[ind] == '\0')
			return (count);
		token_found = find_tokens(str + ind, tokens);
		if (token_found)
		{
			write(1, str + ind, token_found);
			write(1, "\n", 1);
			count++;
			ind += token_found;
		}
		else if (find_tokens(str + ind, tokens) == 0 \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			count++;
			while (find_tokens(str + ind, tokens) == 0 \
				&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
			{
				sep_found = ft_strnmat(sep, str + ind, 1);
				if (sep_found)
				{
					write(1, str + ind, 1);
					ind++;
					while (str[ind] != *sep_found && str[ind])
					{
						write(1, str + ind, 1);
						ind++;
					}
					if (str[ind] == '\0')
						return (-(*sep_found));
					write(1, str + ind, 1);
					ind++;
				}
				else
				{
					write(1, str + ind, 1);
					ind++;
				}
			}
			write(1, "\n", 1);
		}
	}
	return (count);
}

static int	parsing_strlen(char *str, t_token tokens, char **sep)
{
	int		ind;
	int		token_found;
	char	*sep_found;

	ind  = 0;
	token_found = find_tokens(str + ind, tokens);
	if (token_found)
		return (token_found);
	else if (find_tokens(str + ind, tokens) == 0 \
		&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		while (find_tokens(str + ind, tokens) == 0 \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			sep_found = ft_strnmat(sep, str + ind, 1);
			if (sep_found)
			{
				ind++;
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
	return (0);
}

char **tokenization(char *str, t_token tokens, char **sep)
{
	int		wc;
	int		ind;
	int		strcount;
	char	**ret;

	if (str == NULL || *str == '\0')
		return (NULL);
	wc = word_count(str, tokens, sep);
	if (wc < 0)
		return (printf("\nUnclosed |%c|\n", -wc), NULL);
	printf("\nwords in the input ->|%d|\n", wc);
 	return (NULL);
	ret = malloc(sizeof(char *) * (wc + 1));
	if (ret == NULL)
		return (NULL); // CLOSE PROGRAM INSTEAD OF RETURN NULL WHEN WE FIND MEMORY ERRORS?
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
			return (ft_free_matrix(ret), NULL); // CLOSE PROGRAM INSTEAD OF RETURN NULL WHEN WE FIND MEMORY ERRORS?
		str += strcount;
	}
	printf("=========================================================================================\n");
	ft_print_matrix(ret);
	printf("=========================================================================================\n");
 	return (ret);
}

/* 
char	*get_infile(char **mat)
{
	int	ind;

	if (mat == NULL || *mat == NULL)
		return (NULL);
	ind = ft_matlen(mat);
	while (--ind >= 0)
		if (*(mat[ind]) == '<' && )
			if (mat[ind + 1] != NULL)
				return (mat[ind]);
	return (NULL);
} */

// t_table	*tableization(char **mat)
// {
// 	t_table		*table;
// 	t_binary	*head;

// 	if (mat == NULL)
// 		return (NULL);
// 	head->table = malloc(sizeof(t_table));
// 	if (head->table == NULL)
// 		return (NULL);
// 	init_table(table);
// 	get_infile(mat);
	// table->outfiles = get_errfile(mat);
	// table->fd_outfiles = get_outfile(mat);
	// table->cmds = get_cmds(mat);
	// return (table);
// }

void init_tree(void)
{
	btree()->sublvl = 0;
	btree()->type = EMPTY;
	btree()->left_ret = -1;
	btree()->right_ret = -1;
	btree()->subshell_ret = -1;
	btree()->table = NULL;
	btree()->up = NULL;
	btree()->left = NULL;
	btree()->right = NULL;
	btree()->subshell = NULL;
}

// output is:
// 	">>", "&>", ">&", "0>", "1>", "2>"
//	"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
//	"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

// input is:
// 	"<<", "<", "<>" 

int	parsing(char *str)
{
	int		level_count;
	char	*stokens[] = {"(", ")", "&", "|", ">", "<", NULL};
	char	*dtokens[] = {"<>", "||", "&&", ">>", "<<", "&>", ">&", "0>", "1>", "2>", NULL};
	char	*ttokens[] = {"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>", NULL};
	char	*qtokens[] = {"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1", NULL};
	char	*sep[] = {"'", "\"", "`", NULL};
	char 	**mat;
	t_token	tokens;

	tokens.stokens = stokens;
	tokens.dtokens = dtokens;
	tokens.ttokens = ttokens;
	tokens.qtokens = qtokens;
	mat = tokenization(str, tokens, sep);
	if (mat == NULL)
		return (1);
	if (check_syntax(mat))
		return (ft_free_matrix(mat), 1);
	init_tree();
	level_count = separator_count(mat) + 1;
	create_binary_tree(mat, level_count, btree());
	free(mat);
	if (btree()->type = ERROR)
		return (binary_clear(btree()), 1);
	return (0);
}
