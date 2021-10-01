/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 00:17:29 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/21 22:45:11 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_arg_part2(char *start, char **arg, char **new_arg)
{
	char	*part;
	char	*tmp;

	start = *arg;
	while (!ft_strchr("$'\"", **arg))
		(*arg)++;
	part = ft_substr(start, 0, *arg - start);
	tmp = *new_arg;
	*new_arg = ft_strjoin(tmp, part);
	free(tmp);
	free(part);
}

int	parse_arg_part(char *start, char **arg, char **new_arg)
{
	while (*arg && **arg)
	{
		if (ft_strchr("$'\"", **arg))
		{
			*new_arg = ft_substr(start, 0, *arg - start);
			break ;
		}
		(*arg)++;
	}
	if (!**arg)
		return (1);
	return (0);
}

void	parse_arg(t_data *data, char **argv, int i)
{
	char	*arg;
	char	*new_arg;
	char	*start;
	char	*tmp;

	arg = argv[i];
	start = arg;
	if (parse_arg_part(start, &arg, &new_arg))
		return ;
	while (arg && *arg)
	{
		if (*arg == '$')
			open_dollar(data, &arg, &new_arg);
		else if (*arg == '\'')
			open_single_quotes(&arg, &new_arg);
		else if (*arg == '"')
			open_double_quotes(data, &arg, &new_arg);
		else
			parse_arg_part2(start, &arg, &new_arg);
	}
	tmp = argv[i];
	argv[i] = new_arg;
	free(tmp);
}

void	parse_args(t_data *data, int i)
{
	char	**argv;

	argv = data->argvs[i];
	i = -1;
	while (argv[++i])
		parse_arg(data, argv, i);
}
