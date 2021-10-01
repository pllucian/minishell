/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:39:09 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/16 23:47:02 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redirs_part(char **redirs, int *i, char **start, char **end)
{
	*start = (*end)++;
	if (**end == **start)
		(*end)++;
	while (ft_isspace(**end))
		(*end)++;
	while (**end && !ft_isspace(**end) && !ft_strchr("<>", **end))
	{
		if (**end == '\'' || **end == '"')
			*end = ft_strchr(*end + 1, **end);
		(*end)++;
	}
	redirs[*i] = (char *)ft_calloc(*end - *start + 1, sizeof(char));
	ft_strlcpy(redirs[(*i)++], *start, *end - *start + 1);
	(*end)--;
}

void	get_redirs(t_data *data, int i)
{
	char	**redirs;
	char	*start;
	char	*end;

	redirs = data->redirs[i];
	start = data->cmds[i];
	end = start;
	i = 0;
	while (end && *end)
	{
		if (*end == '\'' || *end == '"')
			end = ft_strchr(end + 1, *end);
		else if (ft_strchr("<>", *end))
			get_redirs_part(redirs, &i, &start, &end);
		end++;
	}
}

void	get_args_part2(char **argv, int *i, char **start, char **end)
{
	*start = *end;
	while (**end && !ft_isspace(**end) && !ft_strchr("<>", **end))
	{
		if (**end == '\'' || **end == '"')
			*end = ft_strchr(*end + 1, **end);
		(*end)++;
	}
	argv[*i] = (char *)ft_calloc(*end - *start + 1, sizeof(char));
	ft_strlcpy(argv[(*i)++], *start, *end - *start + 1);
}

void	get_args_part(char **start, char **end)
{
	(*end)++;
	if (**end == **start)
		(*end)++;
	while (ft_isspace(**end))
		(*end)++;
	while (**end && !ft_isspace(**end) && !ft_strchr("<>", **end))
	{
		if (**end == '\'' || **end == '"')
			*end = ft_strchr(*end + 1, **end);
		(*end)++;
	}
	*start = *end;
}

void	get_args(t_data *data, int i)
{
	char	**argv;
	char	*start;
	char	*end;

	argv = data->argvs[i];
	start = data->cmds[i];
	end = start;
	i = 0;
	while (end && *end)
	{
		if (ft_isspace(*end))
			end++;
		else if (ft_strchr("<>", *end))
			get_args_part(&start, &end);
		else
			get_args_part2(argv, &i, &start, &end);
	}
}
