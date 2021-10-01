/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:55:22 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/30 23:13:27 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_pwd(void *data, int i)
{
	(void)data;
	(void)i;
	ft_putendl_fd(((t_data *)data)->cwd, 1);
	return (EXIT_SUCCESS);
}

int	echo_check_n(char *str)
{
	while (str && *str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

int	func_echo(void *data, int i)
{
	char	**argv;
	int		flag_n;

	argv = ((t_data *)data)->argvs[i];
	flag_n = 0;
	argv++;
	if (!*argv)
	{
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
	while (*argv && !ft_strncmp(*argv, "-n", 2) && echo_check_n(*argv + 2))
	{
		flag_n = 1;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*(argv++ + 1))
			ft_putchar_fd(' ', 1);
	}
	if (!flag_n)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
