
#include "../sigma_minishell.h"
#include "jojo_libft/libft.h"

void	binary_clear(t_binary *binary)
{
	if (binary == NULL)
		return ;
	binary_clear(binary->left);
	binary_clear(binary->right);
	binary_clear(binary->subshell);
	cmds_clear(binary->cmds);
	// printf("%s %s\n", binary->logic, binary->print_cmd);
	free (binary->logic);
	free (binary->print_cmd);
	if (binary->up)
		free(binary);
	else
	{
		free(btree()->mat);
		// printf("og matrix deleted\n");
	}
}

void	cmds_clear(t_cmds *cmds)
{
	if (cmds == NULL)
		return ;
	cmds_clear(cmds->next);
	cmds->next = NULL;
	outfile_clear(cmds->outfiles);
	infile_clear(cmds->infiles);
	// printf("%d = ", cmds->expanded);
	// fflush(stdout);
	// ft_print_matrix(cmds->cmd);
	if (cmds->expanded)
		free_matrix(cmds->cmd);
	else
		free_matrix_nodes(cmds->cmd);
	// printf("cmds deleted\n");
	free(cmds);
}

void	infile_clear(t_infile *infile)
{
	if (infile == NULL)
		return ;
	infile_clear(infile->next);
	// printf("%s %s\n", infile->token, infile->file);
	free(infile->file);
	free(infile->token);
	// printf("infile deleted\n");
	free(infile);
}

void	outfile_clear(t_outfile *outfile)
{
	if (outfile == NULL)
		return ;
	outfile_clear(outfile->next);
	// printf("%s %s\n", outfile->token, outfile->file);
	free(outfile->file);
	free(outfile->token);
	// printf("outfile deleted\n");
	free(outfile);
}

void	wild_clear(t_wild *node)
{
	if (node == NULL)
		return ;
	wild_clear(node->next);
	free(node);
}