/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:33:31 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/28 21:14:57 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir_part2(char *start, char **redir, char **new_redir)
{
	char	*part;
	char	*tmp;

	start = *redir;
	while (!ft_strchr("$'\"", **redir))
		(*redir)++;
	part = ft_substr(start, 0, *redir - start);
	tmp = *new_redir;
	*new_redir = ft_strjoin(tmp, part);
	free(tmp);
	free(part);
}

int	parse_redir_part(char *start, char **redir, char **new_redir)
{
	if (!ft_strncmp(*redir, "<<", 2))
		return (1);
	while (*redir && **redir)
	{
		if (ft_strchr("$'\"", **redir))
		{
			*new_redir = ft_substr(start, 0, *redir - start);
			break ;
		}
		(*redir)++;
	}
	if (!**redir)
		return (1);
	return (0);
}

void	parse_redir(t_data *data, char **redirs, int i)
{
	char	*redir;
	char	*new_redir;
	char	*start;
	char	*tmp;

	redir = redirs[i];
	start = redir;
	if (parse_redir_part(start, &redir, &new_redir))
		return ;
	while (redir && *redir)
	{
		if (*redir == '$')
			open_dollar(data, &redir, &new_redir);
		else if (*redir == '\'')
			open_single_quotes(&redir, &new_redir);
		else if (*redir == '"')
			open_double_quotes(data, &redir, &new_redir);
		else
			parse_redir_part2(start, &redir, &new_redir);
	}
	tmp = redirs[i];
	redirs[i] = new_redir;
	free(tmp);
}

void	parse_redirs(t_data *data, int i)
{
	char	**redirs;

	redirs = data->redirs[i];
	i = -1;
	while (redirs[++i])
		parse_redir(data, redirs, i);
}
