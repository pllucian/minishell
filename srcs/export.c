/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 20:23:45 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/21 16:45:10 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_env(char *var)
{
	int		i;

	i = -1;
	while (var[++i] && var[i] != '=')
		ft_putchar_fd(var[i], 1);
	if (var[i])
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&var[++i], 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putchar_fd('\n', 1);
}

void	quik_sort_array(char **array, int first, int last)
{
	char	*tmp;
	int		left;
	int		right;
	int		pivot;

	if (first >= last)
		return ;
	left = first;
	right = last;
	pivot = (first + last) / 2;
	while (left < right)
	{
		while (ft_strncmp(array[left], array[pivot], PATH_MAX) < 0)
			left++;
		while (ft_strncmp(array[right], array[pivot], PATH_MAX) > 0)
			right--;
		if (left <= right)
		{
			tmp = array[left];
			array[left++] = array[right];
			array[right--] = tmp;
		}
	}
	quik_sort_array(array, first, right);
	quik_sort_array(array, left, last);
}

void	print_sorted_env(char **env)
{
	char	**target;
	int		len;
	int		i;

	len = ft_arraylen((void **)env);
	target = (char **)ft_calloc(len + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		target[i] = ft_strdup(env[i]);
	quik_sort_array(target, 0, len - 1);
	i = -1;
	while (target[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		print_var_env(target[i]);
	}
	ft_freearray((void **)target);
}

int	func_export(void *data, int i)
{
	char	**argv;
	char	***env;

	argv = ((t_data *)data)->argvs[i];
	env = &((t_data *)data)->env;
	if (!argv[1])
		print_sorted_env(*env);
	else if (add_vars_env(argv, env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
