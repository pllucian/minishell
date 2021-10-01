/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 22:07:09 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/21 21:06:27 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmds(t_data *data)
{
	char	*start;
	char	*end;
	int		i;

	data->cmds = (char **)ft_calloc(data->num_cmds + 1, sizeof(char *));
	start = data->line;
	end = data->line;
	i = 0;
	while (end && *end)
	{
		if (*end == '|')
		{
			data->cmds[i++] = ft_substr(start, 0, end - start);
			start = ++end;
		}
		if (*end == '\'' || *end == '"')
			end = ft_strchr(end + 1, *end);
		end++;
	}
	data->cmds[i] = ft_substr(start, 0, end - start);
}

int	check_pipes(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!*line || *line == '|')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_num_cmds(char *line)
{
	int		num_pipes;
	char	*tmp;

	tmp = ft_strtrim(line, " \t\n\v\f\r");
	if (*tmp == '|' || *(tmp + ft_strlen(tmp) - 1) == '|')
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	num_pipes = 0;
	while (line && *line)
	{
		if (*line == '|')
		{
			if (check_pipes(++line))
				return (-1);
			num_pipes++;
		}
		if (*line == '\'' || *line == '"')
			line = ft_strchr(line + 1, *line);
		line++;
	}
	return (num_pipes + 1);
}

int	check_quotes(char *line)
{
	char	c;

	c = 0;
	while (line && *line)
	{
		if (*line == '\'' || *line == '"')
		{
			c = *line;
			line = ft_strchr(line + 1, c);
			if (!line)
				break ;
			if (line)
				c = 0;
		}
		line++;
	}
	if (c == '\'')
		ft_putendl_fd \
			("minishell: unexpected EOF while looking for matching `''", 2);
	else if (c == '"')
		ft_putendl_fd \
			("minishell: unexpected EOF while looking for matching `\"'", 2);
	return ((int)c);
}

int	parse_line(t_data *data)
{
	if (check_quotes(data->line))
	{
		g_status = 2;
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		return (EXIT_FAILURE);
	}
	data->num_cmds = get_num_cmds(data->line);
	if (data->num_cmds < 0)
	{
		g_status = 2;
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (EXIT_FAILURE);
	}
	get_cmds(data);
	return (EXIT_SUCCESS);
}
