#include "../sigma_minishell.h"

char    *single_expand(char *str, int ind, int count);

int	get_diff(char *str1, char *str2, int start)
{
	int	ind1;
	int	ind2;

	while (str1[start] == str2[start])
		start++;
	ind1 = ft_strlen(str1);
	ind2 = ft_strlen(str2);
	while (ind1 > start && ind2 > start && str1[ind1] == str2[ind2])
	{
		ind1--;
		ind2--;
	}
	if (ind1 > ind2)
		return (ind1 - start);
	return (ind2 - start);
}

char	*quote(char *str)
{
	char	ch;
	int		ind;
	char	*ret;
	char	*str2;
	int		count;

	ret = str;
	count = -1;
	str2 = ft_strdup(str);
	while (str[++count])
	{
		str = single_expand(str, count, 0);
		if (ft_strcmp(str, str2))
		{
			count += get_diff(str, str2, 0);
			free(str2);
			str2 = ft_strdup(str);
		}
		if (*(str + count) == '\"' || *(str + count) == '\'')
		{
			ind = 0;
			ch = (str + count)[ind];
			ind++;
			while ((str + count)[ind] != ch)
			{
				str = single_expand(str, count, 0);
				if (ft_strcmp(str, str2))
				{
					count += get_diff(str, str2, 0);
					free(str2);
					str2 = ft_strdup(str);
				}
				ind++;
			}
			ft_memmove((str + count) + ind, (str + count) + ind + 1, ft_strlen((str + count) + ind));
			ft_memmove((str + count), (str + count) + 1, ft_strlen((str + count)));
			count += ind - 1;
		}
		else
			count++;
	}
	return (ret);
}

char	*find_os_env(t_os_envs *env, char *str, int count)
{
	while (env)
	{
		if (env->linux_envs && ft_strncmp(env->linux_envs, str, count) == 0)
			return (env->linux_envs);
		env = env->next;
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
		env_var = ft_calloc(1, 1);
	if (env_var == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strdup(str + ind + count);
	if (temp == NULL)
		return (btree()->type = ERROR, free (str), NULL);
	temp = ft_strjoin_free(env_var + count * (*env_var != '\0'), temp, 2);
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
	return (expand(str, ind, 0, 1));
}

char    *single_expand(char *str, int ind, int count)
{
	if (str[ind] == '$' && (ft_isalnum(str[ind + 1]) || str[ind + 1] == '?'
		|| str[ind + 1] == '_' || str[ind + 1] == '\"' || str[ind + 1] == '\''))
	{
		if (str[ind + 1] == '\"' || str[ind + 1] == '\'')
			return (ft_memmove(str + ind, str + ind + 1
			, ft_strlen(str + ind + 1) + 1), str);
	    count++;
	    if (str[ind + 1] == '?')
	        return (expand_last_exit(str, ind, NULL));
	    while (ft_isalnum((str + ind)[count]) || (str + ind)[count] == '_')
	        count++;
	    return (expand_aux(str, ind, count, NULL));
	}
    return (str);
}

char    *expand(char *str, int ind, int count, int flag)
{
    if (str == NULL)
        return (btree()->type = ERROR, NULL);
    while (str[ind])
    {
        if (flag == 1 && str[ind] == '\'' && ++ind)
            while (str[ind] != '\'')
                ind++;
        if (str[ind] == '\"')
            flag = -flag;
        if (str[ind] == '$' && (ft_isalnum(str[ind + 1]) || str[ind + 1] == '?'
			|| str[ind + 1] == '_' || str[ind + 1] == '\"' || str[ind + 1] == '\''))
        {
			if (str[ind + 1] == '\"' || str[ind + 1] == '\'')
				return (ft_memmove(str + ind, str + ind + 1, ft_strlen(str + ind + 1) + 1)
				, expand(str, ind, 0, 1));
            count++;
            if (str[ind + 1] == '?')
                return (expand_last_exit(str, ind, NULL));
            while (ft_isalnum((str + ind)[count]) || (str + ind)[count] == '_')
                count++;
            return (expand_aux(str, ind, count, NULL));
        }
        ind++;
    }
    return (str);
}
