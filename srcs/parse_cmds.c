/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:05:08 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/03 15:43:54 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirs(char *str)
{
	char	c;

	c = *str++;
	if (*str == c)
		str++;
	while (ft_isspace(*str))
		str++;
	if (!*str || *str == '<' || *str == '>' || *str == '|')
	{
		g_status = 2;
		if (c == '<')
			ft_putendl_fd \
				("minishell: syntax error near unexpected token `<'", 2);
		if (c == '>')
			ft_putendl_fd \
				("minishell: syntax error near unexpected token `>'", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_num_args(char *str, int *num_redirs)
{
	int		num_args;

	num_args = 0;
	while (str && *str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			while (*str && !ft_isspace(*str))
			{
				if (*str == '\'' || *str == '"')
					str = ft_strchr(str + 1, *str);
				if (*str == '<' || *str == '>')
				{
					if (check_redirs(str))
						return (-1);
					(*num_redirs)++;
				}
				str++;
			}
			num_args++;
		}
	}
	return (num_args);
}

int	parse_cmd(t_data *data, int i)
{
	int		num_args;
	int		num_redirs;

	num_redirs = 0;
	num_args = get_num_args(data->cmds[i], &num_redirs);
	if (num_args < 0)
		return (EXIT_FAILURE);
	data->argvs[i] = (char **)ft_calloc(num_args + 1, sizeof(char *));
	data->redirs[i] = (char **)ft_calloc(num_redirs + 1, sizeof(char *));
	get_args(data, i);
	get_redirs(data, i);
	parse_args(data, i);
	parse_redirs(data, i);
	return (EXIT_SUCCESS);
}

int	parse_cmds(t_data *data)
{
	int		i;

	data->argvs = (char ***)ft_calloc(data->num_cmds + 1, sizeof(char **));
	data->redirs = (char ***)ft_calloc(data->num_cmds + 1, sizeof(char **));
	data->fds = (t_fd *)ft_calloc(data->num_cmds + 1, sizeof(t_fd));
	data->pipes = (int (*)[2])ft_calloc(data->num_cmds, sizeof(int [2]));
	i = -1;
	while (data->cmds[++i])
	{
		if (parse_cmd(data, i))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
