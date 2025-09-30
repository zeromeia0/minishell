#include "../sigma_minishell.h"

/* void	print_wild(t_wild *head)
{
	while (head)
	{
		printf( "%s\n", head->file);
		head = head->next;
	}
} */

int count_heredocs(t_infile *in)
{
    int count = 0;
    while (in)
    {
        if (ft_strcmp(in->token, "<<") == 0)
            count++;
        in = in->next;
    }
    return count;
}

void get_single_heredoc(char *eof, int fd[2])
{
    char *str;
    char *delimiter = remove_aspas(eof);
    int len = ft_strlen(delimiter);
    int tty_fd;

    if (btree()->global_signal == 130)
        exit(130);
    
    // Ensure we read from terminal for each heredoc
    tty_fd = open("/dev/tty", O_RDONLY);
    if (tty_fd != -1)
    {
        dup2(tty_fd, STDIN_FILENO);
        close(tty_fd);
    }
    
    signal(SIGINT, sig_handle_hererdoc);
    signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT in heredoc
    
    str = readline("> ");
    while (str && ft_strncmp(str, delimiter, len + 1))
    {
        if (fd)
        {
            char *expanded = expand(str, 0, 0, 1);
            write(fd[1], expanded, ft_strlen(expanded));
            write(fd[1], "\n", 1);
            if (expanded != str)
                free(expanded);
        }
        free(str);
        
        if (btree()->global_signal == 130)
            exit(130);
        str = readline("> ");
    }
    
    // Only print warning if we reached EOF (Ctrl+D), not if interrupted by SIGINT
    if (!str && btree()->global_signal != 130) 
    {
        fprintf(stderr, "warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
    }
    
    free(str);
    free(delimiter);
}

void process_heredoc_recursive_simple(t_infile *current, int fd[2])
{
    if (!current)
        return;
    
    if (ft_strcmp(current->token, "<<") == 0)
        get_single_heredoc(current->file, fd);
    process_heredoc_recursive_simple(current->next, fd);
}

void process_all_heredocs(t_infile *in, int fd[2])
{
	// printf("PROCESSING ALL HEREDOCS FELLA\n");
    process_heredoc_recursive_simple(in, fd);
}


// void get_here_doc(char *eof, int fd[2])
// {
//     char *str;
//     char *delimiter = remove_aspas(eof);
//     int len = ft_strlen(delimiter);

// 	if (btree()->global_signal == 130)
// 		exit(130);
// 	signal(SIGINT, sig_handle_hererdoc);
// 	signal(SIGQUIT, handle_quit);
//     str = readline("> ");
//     while (str && ft_strncmp(str, delimiter, len + 1))
//     {
//         if (fd)
//         {
//             char *expanded = expand(str, 0, 0, 1);  // expand input
//             write(fd[1], expanded, ft_strlen(expanded));
//             write(fd[1], "\n", 1);

//             if (expanded != str)
//                 free(expanded);
//         }
//         free(str);
// 		if (btree()->global_signal == 130)
// 			exit(130);
//         str = readline("> ");
//     }
//     free(str);
//     free(delimiter);

//     if (fd)
//         close(fd[1]);
// }

void	single_error_msg(char wc)
{
	ft_putstr_fd("syntax error near unexpected token: `", 2);
	write(1, &wc, 1);
	ft_putstr_fd("'\n", 2);
}

char **tokenization(char *str, t_token tokens, char **sep, int wc)
{
	int		ind;
	int		strcount;
	char	**ret;

	if (wc < 0)
		return (single_error_msg(-wc), NULL);
		// return (printf( "\nUnclosed |%c|\n", -wc), NULL);
	// QUANDO COLOCAS SINGLE QUOTES PROGRAMA NAO ENTRA NO > INPUT


	// printf( "\nwords in the input ->|%d|\n", wc);
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
 	return (ret);
}

void init_tree(char	**mat)
{
	btree()->sublvl = 0;
	btree()->type = EMPTY;
	btree()->left_ret = -1;
	btree()->right_ret = -1;
	btree()->subshell_ret = -1;
	btree()->cmds = NULL;
	btree()->up = NULL;
	btree()->left = NULL;
	btree()->right = NULL;
	btree()->subshell = NULL;
	btree()->global_signal = 0;
	btree()->logic = NULL;
	btree()->print_cmd = NULL;
	btree()->mat = mat;
}

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

int	parsing(char *str)
{
	char	*stokens[] = {"(", ")", "&", "|", ">", "<", NULL};
	char	*dtokens[] = {"||", "&&", ">>", "<<", NULL};
	char	*sep[] = {"'", "\"", "`", NULL};
	char 	**mat;
	t_token	tokens;

	if (str == NULL || *str == '\0')
		return (1);
	tokens.stokens = stokens;
	tokens.dtokens = dtokens;
	mat = NULL;
	if (str != NULL && *str != '\0')
		mat = tokenization(str, tokens, sep, word_count(str, tokens, sep));
	if (mat == NULL)
		return (1);
	// printf( "printing matrix\n");
	// ft_print_matrix(mat);
	// printf( "done printing matrix\n");
	if (check_syntax(mat, tokens))
		return (1);
	init_tree(mat);
	create_binary_tree(mat, sep_count(mat) + 1, btree());
	if (btree()->type == ERROR)
		return (1);
	return (0);
}
