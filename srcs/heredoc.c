/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:25:51 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/30 19:01:31 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc_part(t_data *data, char **line)
{
	char	*new_line;
	char	*start;
	char	*str;

	str = *line;
	start = str;
	while (str && *str)
	{
		if (*str == '$')
		{
			new_line = ft_substr(start, 0, str - start);
			break ;
		}
		str++;
	}
	if (!*str)
		return ;
	while (str && *str)
	{
		if (*str == '$')
			open_dollar(data, &str, &new_line);
	}
	str = *line;
	*line = new_line;
	free(str);
}

void	write_heredoc(t_data *data, int i, char *delimiter, int flag_quotes)
{
	char	*line;

	while (1)
	{
		line = readline(data->ps2);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putendl_fd("')", 2);
			break ;
		}
		if (!ft_strncmp(line, delimiter, (int)(ft_strlen(delimiter) + 1)))
		{
			free(line);
			break ;
		}
		if (!flag_quotes)
			write_heredoc_part(data, &line);
		ft_putendl_fd(line, data->fds[i].fd_read);
		free(line);
	}
}

int	launch_heredoc(t_data *data, int i, char *delimiter, int flag_quotes)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		write_heredoc(data, i, delimiter, flag_quotes);
		exit (EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	if (g_status == 130)
		ft_putchar_fd('\n', 1);
	signal(SIGINT, &handler);
	return (g_status);
}

char	*get_delimiter(char *redir, int *flag_quotes)
{
	char	*delimiter;
	int		i;

	*flag_quotes = 0;
	redir += 2;
	while (ft_isspace(*redir))
		redir++;
	delimiter = (char *)ft_calloc(ft_strlen(redir) + 1, sizeof(char));
	i = -1;
	while (*redir)
	{
		if (ft_strchr("'\"", *redir))
		{
			*flag_quotes = 1;
			redir++;
		}
		else
			delimiter[++i] = *redir++;
	}
	return (delimiter);
}

int	heredoc(t_data *data, char *redir, int i)
{
	char	*delimiter;
	int		flag_quotes;

	if (data->argvs[i][1])
		return (EXIT_SUCCESS);
	data->fds[i].fd_read = open \
		("/tmp/minishell.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	delimiter = get_delimiter(redir, &flag_quotes);
	g_status = launch_heredoc(data, i, delimiter, flag_quotes);
	free(delimiter);
	close(data->fds[i].fd_read);
	data->fds[i].fd_read = open("/tmp/minishell.tmp", O_RDONLY, 0644);
	unlink("/tmp/minishell.tmp");
	return (g_status);
}
