
#include "../minishell.h"

t_outfile	*outfile_new(int fd, char *file, char *token)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	new->fd = fd;
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_infile	*infile_new(char *file, char *token)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	new->file = file;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_cmds	*cmds_new(char **cmd, t_outfile *outfile)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	new->cmd = cmd;
	new->outfiles = outfile;
	new->next = NULL;
	return (new);
}

t_table	*table_new(t_cmds *cmds, t_infile *infile)
{
	t_table	*new;

	new = malloc(sizeof(t_table));
	new->cmds = cmds;
	new->infiles = infile;
	return (new);
}

t_binary	*binary_new(int shlvl, t_type type, t_table *up, t_table *table)
{
	t_binary	*new;

	new = malloc(sizeof(t_table));
	new->type = EMPTY;
	new->sublvl = shlvl;
	new->left_ret = -1;
	new->right_ret = -1;
	new->table = table;
	new->up = up;
	new->left = NULL;
	new->right = NULL;
	new->subshell = NULL;
	return (new);
}
