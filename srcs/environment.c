/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 22:05:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/03 16:46:33 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_check_key(char *str)
{
	char	**tmp;
	char	*key;
	int		i;

	tmp = ft_split(str, '=');
	if (tmp[0][ft_strlen(tmp[0]) - 1] == '+')
		tmp[0][ft_strlen(tmp[0]) - 1] = '\0';
	key = ft_strdup(tmp[0]);
	ft_freearray((void **)tmp);
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		free(key);
		return (NULL);
	}
	i = 0;
	while (key[++i])
	{
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
		{
			free(key);
			return (NULL);
		}
	}
	return (key);
}

char	*get_value_env(char **env, char *key)
{
	int		len;
	int		i;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, len) \
			&& (!env[i][len] || env[i][len] == '='))
			return (ft_strdup(env[i] + len + 1));
	}
	return (NULL);
}

char	**get_ptr_var_env(char **env, char *key)
{
	int		len;
	int		i;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, len) \
			&& (!env[i][len] || env[i][len] == '='))
			return (&env[i]);
	}
	return (NULL);
}

char	**create_new_env(char **env)
{
	char	**new_env;
	char	*tmp;
	int		i;

	new_env = (char **)ft_calloc(ft_arraylen((void **)env) + 1, \
		sizeof(char *));
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			tmp = ft_itoa(ft_atoi(&env[i][6]) + 1);
			new_env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else
			new_env[i] = ft_strdup(env[i]);
	}
	return (new_env);
}
