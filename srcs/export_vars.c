/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:04:19 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/05 11:42:48 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg_export(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	add_var_env_part2(char *arg, char ***env)
{
	char	**new_env;
	char	**tmp;
	int		i;

	new_env = (char **)ft_calloc \
		(ft_arraylen((void **)*env) + 2, sizeof (char *));
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = ft_strdup(arg);
	tmp = *env;
	*env = new_env;
	free(tmp);
	return (EXIT_SUCCESS);
}

int	add_var_env_part(char *arg, char **ptr, char *equals)
{
	char	*tmp;

	if (!equals)
		return (EXIT_SUCCESS);
	if (*(equals - 1) == '+')
	{
		tmp = *ptr;
		*ptr = ft_strjoin(*ptr, ++equals);
		free(tmp);
		return (EXIT_SUCCESS);
	}
	free(*ptr);
	*ptr = ft_strdup(arg);
	return (EXIT_SUCCESS);
}

int	add_var_env(char *arg, char ***env)
{
	char	**ptr;
	char	*equals;
	char	*key;

	equals = ft_strchr(arg, '=');
	key = get_check_key(arg);
	if (!key)
	{
		print_msg_export(arg);
		return (EXIT_FAILURE);
	}
	ptr = get_ptr_var_env(*env, key);
	free(key);
	if (ptr)
		return (add_var_env_part(arg, ptr, equals));
	return (add_var_env_part2(arg, env));
}

int	add_vars_env(char **argv, char ***env)
{
	int		flag_error;
	int		i;

	flag_error = 0;
	i = 0;
	while (argv[++i])
	{
		if (add_var_env(argv[i], env))
			flag_error = 1;
	}
	return (flag_error);
}
