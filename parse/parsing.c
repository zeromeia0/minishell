/*
while (str[ind] == '\t' || str[ind] == ' ' || str[ind] == '\n')
			ind++;
		if (ft_isminishell(str[ind]))
		{
			count++;
			while (ft_isminishell(str[ind]))
			{
				printf("%c", str[ind]);
				ind++;
			}
			printf(" is a word\n\n");
		}
		else if (str[ind] == '\'')
		{
			count++;
			ind++;
			while (str[ind] != '\'' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '\'')
				ind++;
			else
				return (-1 * '\'');
			printf(" is '\n\n");
		}
		else if (str[ind] == '\"')
		{
			count++;
			ind++;
			while (str[ind] != '\"' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '\"')
				ind++;
			else
				return (-1 * '\"');
			printf(" is \"\n\n");
		}
		else if (str[ind] == '`')
		{
			count++;
			ind++;
			while (str[ind] != '`' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '`')
				ind++;
			else
				return (-1 * '`');
			printf("is `\n\n");
		}
		else if (str[ind] == '[')
		{
			count++;
			ind++;
			while (str[ind] != ']' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == ']')
				ind++;
			else
				return (-1 * ']');
			printf(" is '\n\n");
		}
		else if (str[ind] == '{')
		{
			count++;
			ind++;
			while (str[ind] != '}' && str[ind])
			{
				printf("%c", str[ind]);
				ind++;
			}
			if (str[ind] == '}')
				ind++;
			else
				return (-1 * '}');
			printf(" is '\n\n");
		}
		else if (str[ind] == '$')
		{
			count++;
			if (str[ind + 1] == '{')
			{
				while (str[ind] != '}' && str[ind])
				{
					printf("%c", str[ind]);
					ind++;
				}
				if (str[ind] == '}')
				{
					printf("%c is a variable\n\n", str[ind]);
					ind++;
				}
				else
					return (-1 * '}');
			}
			else
			{
				while ((str[ind] != ' ' && str[ind] != '\t') && str[ind])
				{
					printf("%c", str[ind]);
					ind++;
				}
				printf("%c is a variable\n\n", str[ind]);
				while ((str[ind] == ' ' || str[ind] == '\t') && str[ind])
					ind++;
			}
		}
		else
		{
			tokind = 0;
			while (tokens[tokind] && ft_strnstr(str + ind, tokens[tokind], 2) == NULL)
				tokind++;
			if (ft_strnstr(str + ind, tokens[tokind], 2))
			{
				write(1, str + ind, ft_strlen(tokens[tokind]));
				printf(" is %s\n\n", tokens[tokind]);
				ind += ft_strlen(tokens[tokind]);
				count++;
			}
			else if (str[ind])
				ind++;
		}
	if (str[ind] == '\0')
		return (count);
*/

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

int	word_count(char *str, char **stokens, char **dtokens, char **sep)
{
	int		ind;
	int		count;
	char	*sep_found;

	ind  = 0;
	count = 0;
	while (str[ind])
	{
		while (str[ind] == ' ' || str[ind] == '\t' || str[ind] == '\n')
			ind++;
		if (str[ind] == '\0')
			return (count);
		if (ft_strnmat(dtokens, str + ind, 4))
		{
			count++;
			write(1, str + ind, 4);
			write(1, "\n", 1);
			ind += 4;
		}
		if (ft_strnmat(dtokens, str + ind, 3))
		{
			count++;
			write(1, str + ind, 3);
			write(1, "\n", 1);
			ind += 3;
		}
		if (ft_strnmat(dtokens, str + ind, 2))
		{
			count++;
			write(1, str + ind, 2);
			write(1, "\n", 1);
			ind += 2;
		}
		if (ft_strnmat(stokens, str + ind, 1))
		{
			count++;
			write(1, str + ind, 1);
			write(1, "\n", 1);
			ind++;
		}
		if ((ft_strnmat(dtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
			&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
		{
			count++;
			while ((ft_strnmat(dtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
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

static int	parsing_strlen(char *str, char **stokens, char **dtokens, char **sep)
{
	int		ind;
	char	*sep_found;

	ind  = 0;
	// if (*str >= '0' && *str <= '9' && find_fd(*str))
			// return
	// if (ft_strnmat(dtokens, str + ind, 4))
		// return (4);
	// if (ft_strnmat(dtokens, str + ind, 3))
		// return (3);
	if (ft_strnmat(dtokens, str + ind, 2))
		return (2);
	else if (ft_strnmat(stokens, str + ind, 1))
		return (1);
	if ((ft_strnmat(dtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
		&& str[ind] && (str[ind] != ' ' && str[ind] != '\t' && str[ind] != '\n'))
	{
		while ((ft_strnmat(dtokens, str + ind, 2) == NULL && ft_strnmat(stokens, str + ind, 1) == NULL) \
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

char **tokenization(char *str, char **stokens, char **dtokens, char **sep)
{
	int		wc;
	int		ind;
	int		strcount;
	char	**ret;

	wc = word_count(str, stokens, dtokens, sep);
	if (wc < 0)
	{
		printf("\nUnclosed |%c|\n", -wc);

		return (NULL);
	}
	printf("\nwords in the input ->|%d|\n", wc);
 	return (NULL);
	ret = malloc(sizeof(char *) * (wc + 1));
	ret[wc] = NULL;
	ind = -1;
	while (++ind < wc)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str == '\0')
			break ;
		strcount = parsing_strlen(str, stokens, dtokens, sep);
		ret[ind] = ft_strndup(str, strcount);
		str += strcount;
	}
	printf("matrix starts here\n");
	ft_print_matrix(ret);
	printf("matrix ends here\n");
 	return (NULL);
}

void	init_table(t_table *table)
{
	table->cmds = NULL;
	table->infiles = NULL;
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

t_table	*tableization(char **mat)
{
	t_table	*table;

	if (mat == NULL)
		return (NULL);
	table = malloc(sizeof(t_table));
	init_table(table);
	// table->infiles = get_infile(mat);
	// table->outfiles = get_errfile(mat);
	// table->fd_outfiles = get_outfile(mat);
	// table->cmds = get_cmds(mat);
	return (table);
}

t_table *parsing(char *str)
{
	char 	**mat;
	char	*sep[] = {"'", "\"", "`", NULL};
	char	*stokens[] = {"&", "|", ">", "<", NULL};
	char	*dtokens[] = {/* "<>", */ ">>", "<<", "&>", ">&", "0>", "1>", "2>", NULL};
	// char	*ttokens[] = {"&>>", "0>>", "1>>", "2>>", NULL};
	// char	*qtokens[] = {"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1", NULL};
	t_table	*table;

	// create_binary_tree(str);
	mat = tokenization(str, stokens, dtokens, sep);
	table = tableization(mat);
	return (table);
}