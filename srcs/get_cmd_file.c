/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:30:33 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/01 01:20:55 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_file_sh(char ***argv)
{
	char		**new_argv;
	char		**tmp;
	int			i;

	new_argv = (char **)ft_calloc \
		(ft_arraylen((void **)*argv) + 2, sizeof(char *));
	new_argv[0] = ft_strdup((*argv)[0]);
	i = -1;
	while ((*argv)[++i])
		new_argv[i + 1] = (*argv)[i];
	tmp = *argv;
	*argv = new_argv;
	free(tmp);
	return (ft_strdup("/bin/sh"));
}

int	file_exec(char **argv, char **env)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(execve(argv[0], argv, env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	if (g_status == 130)
		ft_putchar_fd('\n', 1);
	if (g_status == 131)
		ft_putendl_fd("Quit", 1);
	signal(SIGINT, &handler);
	if (g_status == 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	file_mode_isx(char *arg)
{
	struct stat	buf;

	stat(arg, &buf);
	if (buf.st_uid == ((uid_t)get_user_group_id("-u")))
	{
		if (buf.st_mode & S_IXUSR)
			return (true);
		else
			return (false);
	}
	else if (buf.st_uid == ((uid_t)get_user_group_id("-g")))
	{
		if (buf.st_mode & S_IXGRP)
			return (true);
		else
			return (false);
	}
	else if (buf.st_mode & S_IXOTH)
		return (true);
	return (false);
}

char	*get_cmd_file_part(char ***argv, char **env)
{
	if (file_exec(*argv, env))
		return (get_cmd_file_sh(argv));
	return (NULL);
}

char	*get_cmd_file(char ***argv, char **env)
{
	struct stat	buf;
	char		*msg;

	if (stat((*argv)[0], &buf))
		g_status = 127;
	else if (S_ISDIR(buf.st_mode))
	{
		g_status = 126;
		errno = EISDIR;
	}
	else if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode) \
		|| !file_mode_isx((*argv)[0]))
	{
		g_status = 126;
		errno = EACCES;
	}
	else
		return (get_cmd_file_part(argv, env));
	msg = ft_strjoin("minishell: ", (*argv)[0]);
	perror(msg);
	free(msg);
	return (NULL);
}
