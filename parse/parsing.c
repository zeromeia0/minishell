#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

/* int	find_fd_red(char *str)
char **tokenization(char *str)
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
	// if (ft_strnmat(tokens.qtokens, str, 4))
		// return (4);
	// if (ft_strnmat(tokens.ttokens, str, 3))
		// return (3);
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
			// write(1, str + ind, token_found);
			// write(1, "\n", 1);
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
					// write(1, str + ind, 1);
					ind++;
					while (str[ind] != *sep_found && str[ind])
					{
						// write(1, str + ind, 1);
						ind++;
					}
					if (str[ind] == '\0')
						return (-(*sep_found));
					// write(1, str + ind, 1);
					ind++;
				}
				else
				{
					// write(1, str + ind, 1);
					ind++;
				}
			}
			// write(1, "\n", 1);
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
	printf("========================================================\n");
	ft_print_matrix(ret);
	printf("========================================================\n");
 	return (ret);
}

void init_tree(char	**mat)
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
	btree()->mat = mat;
}

// output is:
// 	">>", "&>", ">&", "0>", "1>", "2>"
//	"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>"
//	"0>&1", "1>&0", "0>&2", "2>&0", "1>&2", "2>&1"

// input is:
// 	"<<", "<", "<>" 



int	find_syntax(char *str, t_token tokens)
{
	if (ft_strnmat(tokens.dtokens, str, 2))
		return (2);
	if (ft_strnmat(tokens.stokens, str, 1))
		return (1);
	return (0);
}


/* int	check_syntax(char **mat, t_token tokens)
{
	int		ind;
	char	*token_found;
	char	*str;
	char	*stokens[] = {"&", "|", NULL};
	char	*dtokens[] = {"||", "&&", ">>", NULL};

	ind = 0;
	token_found = find_tokens(mat + ind, tokens);
	
} */

int	separator_count(char **mat)
{
	int	count;

	count = 0;
	while (*mat)
	{
		if (strncmp(*mat, "&", 2))
			count++;
		mat++;
	}
	return (count);
}
/* 
char	*dtokens[] = {"<>", "||", "&&", ">>", "<<", "&>", ">&", "0>", "1>", "2>", NULL};
char	*ttokens[] = {"0<>", "1<>", "2<>", "&>>", "0>>", "1>>", "2>>", NULL};
char	*qtokens[] = {"0>&1", "1>&0", / ignore left? /"0>&2", "2>&0", "1>&2", "2>&1", NULL};
tokens.ttokens = ttokens;
tokens.qtokens = qtokens;
 if (check_syntax(mat, tokens))
	 printf("wrongggggggg\n");
 else 
	 printf("rightttttttttt\n");
	 return (ft_free_matrix(mat), 1);
 */

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

char	*expand(char *str)
{
	int		ind;
	int		count;
	char	*temp;
	char	*strcp;

	ind = 0;
	while (str[ind])
	{
		count = 0;
		if (str[ind] == '$' && ft_isalnum(str[ind + 1]))
		{
			ind++;
			while ((str + ind)[count] != ' ' && str[ind + 1] != '\0')
				count++;
			strcp = ft_strdup(str + ind + count);
			temp = ft_strndup(str + ind, count);

			temp = ft_strnmat(mat, "$", 1);
			temp = ft_strnmat(btree()->env, *temp, 1);

			return (str);
		}
		else
			ind++;
	}
	return (str);
}

void	get_here_doc(char *eof, int fd[2])
{
	char	*str;
	// char	strfinal[1024];
	int		len;

	len = ft_strlen(eof);
	str = readline("> ");
	while (ft_strncmp(str, eof, len + 1))
	{
		str = expand(str);
		write (fd[1], str, ft_strlen(str));
		write (fd[1], "\n", 1);
		free (str);
		str = readline("> ");
	}
	free (str);
	// read(fd[0], strfinal, 1023);
	// printf("%s", strfinal);
	close (fd[0]);
	close (fd[1]);
}

int	parsing(char *str)
{
	/* char	*stokens[] = {"(", ")", "&", "|", ">", "<", NULL};
	char	*dtokens[] = {"||", "&&", ">>", "<<", NULL};
	char	*sep[] = {"'", "\"", "`", NULL};
	char 	**mat;
	t_token	tokens;

	if (str == NULL || *str == '\0')
		return (1);
	tokens.stokens = stokens;
	tokens.dtokens = dtokens;
	mat = tokenization(str, tokens, sep);
	if (mat == NULL)
		return (1);
	init_tree(mat);
	create_binary_tree(mat, separator_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (binary_clear(btree()), 1); */
	int			fd[2];

	if (pipe(fd))
		return (printf("error\n"));
	get_here_doc(str, fd);
	return (0);
}
