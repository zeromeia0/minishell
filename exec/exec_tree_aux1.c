/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:12:18 by vivaz-ca          #+#    #+#             */
/*   Updated: 2025/10/09 13:01:09 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

char	**build_system_paths(char *cmd_name, char **paths)
{
	char	**final_str;
	char	*tmp;
	int		i;

	final_str = malloc(sizeof(char *) * (ft_matlen(paths) + 1));
	if (!final_str)
		return (NULL);
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		final_str[i] = ft_strjoin(tmp, cmd_name);
		free(tmp);
		i++;
	}
	final_str[i] = NULL;
	return (final_str);
}

char	**buildup_path(t_cmds *cmd, char **args, char **envp)
{
	char	**final_str;
	char	**paths_to_search;

	if (has_builtin(cmd))
	{
		final_str = malloc(sizeof(char *) * 2);
		if (!final_str)
			return (NULL);
		final_str[0] = ft_strdup(cmd->cmd[0]);
		final_str[1] = NULL;
		return (final_str);
	}
	if (is_system_path_command(cmd->cmd[0], envp))
	{
		paths_to_search = get_paths_to_search(envp);
		final_str = build_system_paths(cmd->cmd[0], paths_to_search);
		if (paths_to_search)
			ft_free_matrix(paths_to_search);
		return (final_str);
	}
	final_str = malloc(sizeof(char *));
	if (!final_str)
		return (NULL);
	final_str[0] = NULL;
	return (final_str);
}

int	ensure_outfile(t_outfile *out)
{
	int	fd;

	if (!out || !out->file)
		return (-1);
	fd = open(out->file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		return (btree()->cmds->flag_to_exec = 1, my_ffprintf(out->file,
				"Permission denied\n"), -1);
	}
	close(fd);
	return (0);
}

int	check_infiles(t_cmds *cmds)
{
	t_infile	*current_infile;

	if (!cmds || !cmds->infiles)
		return (1);
	current_infile = cmds->infiles;
	while (current_infile)
	{
		if (ft_strcmp(current_infile->token, "<<") != 0)
		{
			if (access(current_infile->file, F_OK) != 0)
			{
				cmds->flag_to_exec = 1;
				my_ffprintf(current_infile->file,
					"No such file or directory\n");
				return (0);
			}
			if (access(current_infile->file, R_OK) != 0)
				return (cmds->flag_to_exec = 1,
					my_ffprintf(current_infile->file, "Permission denied\n"),
					0);
		}
		current_infile = current_infile->next;
	}
	return (1);
}

int is_cmd_valid(t_cmds *cmd, char **args, char **envp)
{
    char **paths;
    int i;
    int found;

    if (has_builtin(cmd))
        return (1);

    paths = buildup_path(cmd, args, envp);
    if (!paths)
        return (0);

    i = 0;
    while (paths[i])
    {
        if (access(paths[i], F_OK | X_OK) == 0)
            break;
        i++;
    }
    found = (paths[i] != NULL);
    ft_free_matrix(paths);
    return (found);
}

