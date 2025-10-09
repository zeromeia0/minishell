#include "../sigma_minishell.h"

void	syntax_error_msg(char *str)
{
	write(1, "syntax error near unexpected token: `", 38);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
}

void	single_error_msg(char wc)
{
	ft_putstr_fd("syntax error near unexpected token: `", 2);
	write(1, &wc, 1);
	ft_putstr_fd("'\n", 2);
}
