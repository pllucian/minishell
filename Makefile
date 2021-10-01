# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/01 19:29:24 by pllucian          #+#    #+#              #
#    Updated: 2021/10/03 18:03:00 by pllucian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES =	minishell.c \
		environment.c \
		history_builtins.c \
		handler_free.c \
		parse_line.c \
		parse_cmds.c \
		get_args_redirs.c \
		parse_args.c \
		parse_redirs.c \
		dollar_quotes.c \
		launch.c \
		open_redirs.c \
		heredoc.c \
		replace_fds.c \
		get_cmd.c \
		get_cmd_file.c \
		get_user_group_id.c \
		echo_pwd.c \
		cd.c \
		export.c \
		export_vars.c \
		unset_env_exit.c \
		get_next_line.c \
		utils.c \
		utils_free.c

SRCS = $(addprefix srcs/, $(FILES))

OBJS = $(addprefix objs/, $(FILES:.c=.o))

INCL = includes/minishell.h

NAME = minishell

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

objs/%.o:	srcs/%.c
			@ [ -d objs ] || mkdir -p objs
			$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft

$(NAME):	$(OBJS) $(INCL)
			make bonus -C ./libft
			$(CC) -o $@ $(OBJS) -Llibft -lft -lreadline

all:		$(NAME)

clean:
			make clean -C ./libft
			$(RM)r $(OBJS) objs

fclean:		clean
			make fclean -C ./libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
