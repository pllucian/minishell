/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:30:23 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/28 11:49:07 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_data *data)
{
	free_line_data(data);
	free_init_data(data);
	exit(g_status);
}

void	init_prompt(t_data *data)
{
	char	*tmp;

	data->cwd = getcwd(NULL, 0);
	data->ps1 = ft_strjoin("\e[1;36mminishell\e[0m:\e[1;34m", data->cwd);
	tmp = data->ps1;
	data->ps1 = ft_strjoin(tmp, "\e[0m$ ");
	free(tmp);
	data->ps2 = ft_strdup("> ");
}

t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*msg;

	g_status = 0;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (argc > 1)
	{
		msg = ft_strjoin("minishell: ", argv[1]);
		errno = E2BIG;
		g_status = errno;
		perror(msg);
		free(msg);
		free(data);
		exit(g_status);
	}
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	data->env = create_new_env(env);
	init_builtins(data);
	init_history(data);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = init_data(argc, argv, env);
	while (1)
	{
		free_line_data(data);
		init_prompt(data);
		data->line = readline(data->ps1);
		if (!data->line)
		{
			ft_putendl_fd("exit", 1);
			exit_free(data);
		}
		if (ft_strisspace(data->line))
			continue ;
		if (data->line && *data->line && !ft_isspace(*data->line))
			ft_add_history(data);
		if (parse_line(data) || parse_cmds(data))
			continue ;
		launch_cmds(data);
	}
	return (EXIT_SUCCESS);
}
