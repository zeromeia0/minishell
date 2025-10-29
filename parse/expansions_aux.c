/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:36:30 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/28 18:29:30 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sigma_minishell.h"

char	*find_os_env(t_os_envs *ev, char *str, int count)
{
	while (ev)
	{
		if (ev->linux_envs && ft_strncmp(ev->linux_envs, str, count) == 0)
			return (ft_strchr(ev->linux_envs, '=') + 1);
		ev = ev->next;
	}
	return (NULL);
}

char	*expand_aux(char *str, int ind, int count, char *temp)
{
	char	*env_var;

	temp = ft_strndup(str + ind + 1, count - 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(temp, "=", 1);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	env_var = find_os_env(btree()->os_env, temp, count);
	free(temp);
	if (env_var == NULL)
		env_var = "\0";
	if (env_var == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strdup(str + ind + count);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(env_var, temp, 2);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	str[ind] = '\0';
	str = ft_strjoin_free(str, temp, 0);
	return (str);
}

char	*expand_last_exit(char *str, int ind, char *temp)
{
	char	*env_var;

	env_var = ft_itoa(btree()->exit_status);
	if (env_var == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strdup(str + ind + 2);
	if (temp == NULL)
		return (btree()->type = ERROR, free (env_var), free (str), NULL);
	temp = ft_strjoin_free(env_var, temp, 0);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	str[ind] = '\0';
	str = ft_strjoin_free(str, temp, 0);
	return (str);
}

char	*single_expand(char *s, int i, int count)
{
	if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '?'
			|| s[i + 1] == '_' || s[i + 1] == '\"' || s[i + 1] == '\''))
	{
		if (s[i + 1] == '\"' || s[i + 1] == '\'')
			return (ft_memmove(s + i, s + i + 1
					, ft_strlen(s + i + 1) + 1), s);
		count++;
		if (s[i + 1] == '?')
			return (expand_last_exit(s, i, NULL));
		while (ft_isalnum((s + i)[count]) || (s + i)[count] == '_')
			count++;
		return (expand_aux(s, i, count, NULL));
	}
	return (s);
}

char	*expand(char *s, int i, int count, int flag)
{
	if (s == NULL)
		return (btree()->type = ERROR, NULL);
	while (s[i])
	{
		if (flag == 1 && s[i] == '\'' && ++i)
			while (s[i] != '\'')
				i++;
		if (s[i] == '\"')
			flag = -flag;
		if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '?'
				|| s[i + 1] == '_' || s[i + 1] == '\"' || s[i + 1] == '\''))
		{
			if (s[i + 1] == '\"' || s[i + 1] == '\'')
				return (ft_memmove(s + i, s + i + 1
						, ft_strlen(s + i + 1) + 1), expand(s, i, 0, 1));
			count++;
			if (s[i + 1] == '?')
				return (expand_last_exit(s, i, NULL));
			while (ft_isalnum((s + i)[count]) || (s + i)[count] == '_')
				count++;
			return (expand_aux(s, i, count, NULL));
		}
		i++;
	}
	return (s);
}
