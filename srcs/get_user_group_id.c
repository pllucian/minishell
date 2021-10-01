/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_group_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 23:14:05 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/27 23:51:18 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_user_group_id_part(char *file)
{
	char	*line;
	int		fd;
	int		id;

	fd = open(file, O_RDONLY, 0644);
	get_next_line(fd, &line);
	close(fd);
	id = ft_atoi(line);
	free(line);
	return (id);
}

int	get_user_group_id(char *target)
{
	char	**tmp;
	char	*file;
	int		fd;
	int		id;

	file = "/tmp/minishell.tmp";
	tmp = (char **)ft_calloc(3, sizeof(char *));
	tmp[0] = ft_strdup("/usr/bin/id");
	tmp[1] = ft_strdup(target);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!fork())
	{
		dup2(fd, 1);
		exit(execve(tmp[0], tmp, NULL));
	}
	wait(NULL);
	id = get_user_group_id_part(file);
	close(fd);
	unlink(file);
	ft_freearray((void **)tmp);
	return (id);
}
