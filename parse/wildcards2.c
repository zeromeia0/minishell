/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:33:52 by namejojo          #+#    #+#             */
/*   Updated: 2025/09/24 18:33:53 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

char	**bind_mat_lst_aux(char **mat, char **ret, int count, t_wild *head)
{
	int	ind;

	ind = 0;
	while (ind < count)
	{
		ret[ind] = ft_strdup(mat[ind]);
		ind++;
	}
	while (head)
	{
		ret[ind] = head->file;
		head = head->next;
		ind++;
	}
	while (mat[++count])
	{
		ret[ind] = ft_strdup(mat[count]);
		ind++;
	}
	return (ret);
}

char	**bind_mat_lst(char **mat, int count, t_wild *head, int ind)
{
	char	**ret;

	if (head == NULL)
		return (mat);
	ind = ft_matlen(mat) + wildsize(head) - 1;
	ret = malloc(sizeof(char *) * (ind + 1));
	if (ret == NULL)
		return (btree()->type = ERROR, NULL);
	ret[ind] = NULL;
	sort_wild(head);
	ret = bind_mat_lst_aux(mat, ret, count, head);
	wild_clear(head);
	return (ret);
}

int	hidden_files(char *file, char *start)
{
	if (*file != '.' && *start != '.')
		return (1);
	if (*file == '.' && *start == '.')
		return (1);
	return (0);
}

t_wild	*read_dir(char *dir, t_wild *head, char *start)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*str;

	directory = opendir(dir);
	if (directory == NULL)
		return (btree()->type = ERROR, NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (hidden_files(entry->d_name, start))
		{
			str = ft_strdup(entry->d_name);
			add_wild_back(&head, wild_new(str, entry->d_type));
		}
		if (btree()->type == ERROR)
			return (wild_clear(head), closedir(directory), NULL);
		entry = readdir(directory);
	}
	closedir(directory);
	return (head);
}
