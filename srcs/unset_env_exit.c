/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:18:14 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/03 21:08:59 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_isnum(char *str)
{
	int					sign;

	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!ft_strisdigit(str))
		return (false);
	if (sign == 1 && ft_strlen(str) >= 19 && ft_atoll(str) == -1)
		return (false);
	if (sign == -1 && ft_strlen(str) >= 19 && ft_atoll(str) == 0)
		return (false);
	return (true);
}

int	func_exit(void *data, int i)
{
	char	**argv;
	int		len;

	argv = ((t_data *)data)->argvs[i];
	len = ft_arraylen((void **)argv);
	ft_putendl_fd("exit", 1);
	if (len > 1 && !exit_isnum(argv[1]))
	{
		g_status = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (len == 2 && exit_isnum(argv[1]))
	{
		g_status = ft_atoll(argv[1]) % 256;
	}
	else if (len > 2 && exit_isnum(argv[1]))
	{
		g_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	exit_free((t_data *)data);
	return (EXIT_SUCCESS);
}

int	func_env(void *data, int i)
{
	char	**argv;
	char	**env;

	argv = ((t_data *)data)->argvs[i];
	env = ((t_data *)data)->env;
	if (ft_arraylen((void **)argv) > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (env[++i] && ft_strchr(env[i], '='))
		ft_putendl_fd(env[i], 1);
	return (EXIT_SUCCESS);
}

void	del_var_env(char *arg, char ***env)
{
	char	**new_env;
	char	**ptr;
	char	**tmp;
	int		i;

	ptr = get_ptr_var_env(*env, arg);
	if (!ptr)
		return ;
	new_env = (char **)ft_calloc \
		(ft_arraylen((void **)*env), sizeof (char *));
	i = -1;
	while ((*env)[++i] != *ptr)
		new_env[i] = (*env)[i];
	free(*ptr);
	while ((*env)[++i])
		new_env[i - 1] = (*env)[i];
	tmp = *env;
	*env = new_env;
	free(tmp);
}

int	func_unset(void *data, int i)
{
	char	**argv;
	char	***env;

	argv = ((t_data *)data)->argvs[i];
	env = &((t_data *)data)->env;
	if (!argv[1])
		return (EXIT_SUCCESS);
	i = 0;
	while (argv[++i])
		del_var_env(argv[i], env);
	return (EXIT_SUCCESS);
}
