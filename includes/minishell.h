/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:29:20 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/05 11:42:45 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NUM_BUILTINS 7

int			g_status;

typedef struct s_fd
{
	int		fd_read;
	int		fd_write;
}			t_fd;

typedef struct s_builtin
{
	char	*cmd;
	int		(*func)(void *, int);
}			t_builtin;

typedef struct s_data
{
	char		*cwd;
	char		*ps1;
	char		*ps2;
	char		*line;
	char		**env;
	t_builtin	*builtins;
	int			num_cmds;
	char		**cmds;
	char		***argvs;
	char		***redirs;
	t_fd		*fds;
	int			(*pipes)[2];
}			t_data;

int			get_next_line(int fd, char **line);

size_t		ft_arraylen(void **array);
int			ft_isspace(int c);
int			ft_strisspace(char *str);
int			ft_strisdigit(char *str);
long long	ft_atoll(const char *nptr);

void		ft_freearray(void **array);
void		ft_freearray2(void ***array2);
void		free_builtins(t_builtin *builtins);
void		close_fds(t_data *data);

int			func_exit(void *data, int i);
int			func_env(void *data, int i);
void		del_var_env(char *arg, char ***env);
int			func_unset(void *data, int i);

void		print_msg_export(char *arg);
int			add_var_env_part2(char *arg, char ***env);
int			add_var_env_part(char *arg, char **ptr, char *equals);
int			add_var_env(char *arg, char ***env);
int			add_vars_env(char **argv, char ***env);

void		print_var_env(char *var);
void		quik_sort_array(char **array, int first, int last);
void		print_sorted_env(char **env);
int			func_export(void *data, int i);

void		cd_update_env(char **cwd, char **env);
int			cd_path(char **cwd, char **env, char *path);
int			func_cd(void *data, int i);

int			func_pwd(void *data, int i);
int			echo_check_n(char *str);
int			func_echo(void *data, int i);

int			get_user_group_id_part(char *file);
int			get_user_group_id(char *target);

char		*get_cmd_file_sh(char ***argv);
int			file_exec(char **argv, char **env);
int			file_mode_isx(char *arg);
char		*get_cmd_file(char ***argv, char **env);

char		*get_cmd_path(char **argv, char *path);
char		*get_cmd_paths(char **argv, char **env);
char		*get_cmd_source(char **argv);
char		*get_cmd(t_data *data, int i);

void		replace_fds_pipe(t_data *data, int i);
void		replace_fds_redir(t_data *data, int i);
void		replace_fds(t_data *data, int i);

void		write_heredoc_part(t_data *data, char **line);
void		write_heredoc(t_data *data, int i, char *delim, int flag);
int			launch_heredoc(t_data *data, int i, char *delim, int flag);
char		*get_delimiter(char *redir, int *flag_quotes);
int			heredoc(t_data *data, char *redir, int i);

int			open_redir_output(t_data *data, char *redir, int i);
int			open_redir_input(t_data *data, char *redir, int i);
int			open_redir_output_append(t_data *data, char *redir, int i);
int			open_redir(t_data *data, char *redir, int i);
int			open_redirs(t_data *data);

void		launch_cmd_fork(t_data *data, int i, char *cmd);
void		launch_cmd(t_data *data, int i);
void		launch_cmds(t_data *data);

void		open_double_quotes(t_data *data, char **str, char **new_str);
void		open_single_quotes(char **str, char **new_str);
void		dollar_env_part(t_data *data, char **s, char **new_s, char *start);
void		dollar_env(t_data *data, char **str, char **new_str);
void		open_dollar(t_data *data, char **str, char **new_str);

void		parse_redir_part2(char *start, char **redir, char **new_redir);
int			parse_redir_part(char *start, char **redir, char **new_redir);
void		parse_redir(t_data *data, char **redirs, int i);
void		parse_redirs(t_data *data, int i);

void		parse_arg_part2(char *start, char **arg, char **new_arg);
int			parse_arg_part(char *start, char **arg, char **new_arg);
void		parse_arg(t_data *data, char **argv, int i);
void		parse_args(t_data *data, int i);

void		get_redirs_part(char **redirs, int *i, char **start, char **end);
void		get_redirs(t_data *data, int i);
void		get_args_part2(char **argv, int *i, char **start, char **end);
void		get_args_part(char **start, char **end);
void		get_args(t_data *data, int i);

int			check_redirs(char *str);
int			get_num_args(char *str, int *num_redirs);
int			parse_cmd(t_data *data, int i);
int			parse_cmds(t_data *data);

void		get_cmds(t_data *data);
int			check_pipes(char *line);
int			get_num_cmds(char *line);
int			check_quotes(char *line);
int			parse_line(t_data *data);

int			is_builtin(t_data *data, char *cmd);
void		init_builtins(t_data *data);
void		ft_add_history(t_data *data);
void		init_history(t_data *data);

char		*get_check_key(char *str);
char		*get_value_env(char **env, char *key);
char		**get_ptr_var_env(char **env, char *key);
char		**create_new_env(char **env);

void		handler(int signal);
void		free_line_data_part(t_data *data);
void		free_line_data(t_data *data);
void		free_init_data(t_data *data);

void		exit_free(t_data *data);
void		init_prompt(t_data *data);
t_data		*init_data(int argc, char **argv, char **env);

#endif
