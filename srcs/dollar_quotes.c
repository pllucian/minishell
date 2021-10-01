/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:41:17 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/21 22:52:37 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_double_quotes(t_data *data, char **str, char **new_str)
{
	char	*start;
	char	*part;
	char	*tmp;

	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$')
			open_dollar(data, str, new_str);
		else
		{
			start = *str;
			while (!ft_strchr("$\"", **str))
				(*str)++;
			part = ft_substr(start, 0, *str - start);
			tmp = *new_str;
			*new_str = ft_strjoin(tmp, part);
			free(tmp);
			free(part);
		}
	}
	(*str)++;
}

void	open_single_quotes(char **str, char **new_str)
{
	char	*start;
	char	*part;
	char	*tmp;

	start = *str + 1;
	*str = ft_strchr(start, '\'');
	part = ft_substr(start, 0, *str - start);
	tmp = *new_str;
	*new_str = ft_strjoin(tmp, part);
	free(tmp);
	free(part);
	(*str)++;
}

void	dollar_env_part(t_data *data, char **str, char **new_str, char *start)
{
	char	*value;
	char	*tmp;

	tmp = ft_substr(start, 0, *str - start);
	value = get_value_env(data->env, tmp + 1);
	free(tmp);
	if (!value)
		value = ft_strdup("");
	tmp = *new_str;
	*new_str = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
}

void	dollar_env(t_data *data, char **str, char **new_str)
{
	char	*start;
	char	*part;
	char	*tmp;

	start = *str;
	while (*str && **str)
	{
		(*str)++;
		if (**str && !ft_isalpha(**str) && !ft_isdigit(**str) && **str != '_')
			break ;
		if (**str && !ft_isalpha(*(start + 1)) && *(start + 1) != '_')
		{
			(*str)++;
			break ;
		}
	}
	if (*str - start < 2)
	{
		part = ft_substr(start, 0, *str - start);
		tmp = *new_str;
		*new_str = ft_strjoin(tmp, part);
		free(tmp);
		free(part);
	}
	dollar_env_part(data, str, new_str, start);
}

void	open_dollar(t_data *data, char **str, char **new_str)
{
	char	*value;
	char	*tmp;

	if (!ft_strncmp(*str, "$?", 2))
	{
		value = ft_itoa(g_status);
		tmp = *new_str;
		*new_str = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
		(*str) += 2;
	}
	else
		dollar_env(data, str, new_str);
}
