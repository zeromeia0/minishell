/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:47:16 by vvazzs            #+#    #+#             */
/*   Updated: 2025/09/24 12:50:33 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sigma_minishell.h"

static char	*resolve_path(const char *path, char *resolved)
{
	char	buffer[PATH_MAX];
	char	*p;
	ssize_t	len;
	size_t	buflen;
	char	*res;
	char	*last;
	char	*component_start;
	size_t	comp_len;

	if (!path || !*path)
		return (errno = EINVAL, NULL);
	if (path[0] == '/')
	{
		strncpy(buffer, path, sizeof(buffer) - 1);
		buffer[sizeof(buffer) - 1] = '\0';
	}
	else
	{
		if (!getcwd(buffer, sizeof(buffer)))
			return (NULL);
		buflen = strlen(buffer);
		if (buflen + 1 + strlen(path) >= sizeof(buffer))
			return (errno = ENAMETOOLONG, NULL);
		if (buflen > 0 && buffer[buflen - 1] != '/')
			strcat(buffer, "/");
		strcat(buffer, path);
	}
	p = buffer;
	res = resolved;
	last = resolved + PATH_MAX - 1;
	*res = '\0';
	if (*p == '/')
	{
		*res++ = '/';
		p++;
	}
	while (*p)
	{
		while (*p == '/')
			p++;
		if (!*p)
			break ;
		component_start = p;
		while (*p && *p != '/')
			p++;
		comp_len = p - component_start;
		if (comp_len == 1 && component_start[0] == '.')
			continue ;
		if (comp_len == 2 && component_start[0] == '.'
			&& component_start[1] == '.')
		{
			if (res > resolved + 1)
			{
				res--;
				while (res > resolved && *res != '/')
					res--;
				if (res >= resolved)
					*res = '\0';
			}
			continue ;
		}
		if (res > resolved && *(res - 1) != '/')
		{
			if (res < last)
				*res++ = '/';
			else
				return (errno = ENAMETOOLONG, NULL);
		}
		while (component_start < p)
		{
			if (res < last)
				*res++ = *component_start++;
			else
				return (errno = ENAMETOOLONG, NULL);
		}
		*res = '\0';
	}
	if (resolved[0] == '\0')
		strcpy(resolved, "/");
	return (resolved);
}

char	*my_realpath(const char *path, char *resolved_path)
{
	char buffer[PATH_MAX];

	if (!path)
		return (errno = EINVAL, NULL);
	if (!resolved_path)
	{
		resolved_path = malloc(PATH_MAX);
		if (!resolved_path)
			return (errno = ENOMEM, NULL);
	}
	char temp[PATH_MAX];
	strncpy(temp, path, sizeof(temp) - 1);
	temp[sizeof(temp) - 1] = '\0';
	ssize_t len;
	int max_symlinks = 32; // Prevent infinite loops
	int symlink_count = 0;
	while (symlink_count++ < max_symlinks)
	{
		len = readlink(temp, buffer, sizeof(buffer) - 1);
		if (len == -1)
		{
			if (errno == EINVAL)
				break ;
			if (resolved_path != path)
				free(resolved_path);
			return (NULL);
		}
		buffer[len] = '\0';
		if (buffer[0] == '/')
			strncpy(temp, buffer, sizeof(temp) - 1);
		else
		{
			char *last_slash = strrchr(temp, '/');
			if (last_slash)
			{
				*(last_slash + 1) = '\0';
				if (strlen(temp) + strlen(buffer) >= sizeof(temp))
				{
					errno = ENAMETOOLONG;
					if (resolved_path != path)
						free(resolved_path);
					return (NULL);
				}
				strcat(temp, buffer);
			}
			else
				strncpy(temp, buffer, sizeof(temp) - 1);
		}
	}
	if (symlink_count >= max_symlinks)
	{
		errno = ELOOP;
		if (resolved_path != path)
			free(resolved_path);
		return (NULL);
	}
	if (!resolve_path(temp, resolved_path))
	{
		if (resolved_path != path)
			free(resolved_path);
		return (NULL);
	}
	return (resolved_path);
}
