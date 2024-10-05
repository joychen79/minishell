# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:50:55 by rrimonte          #+#    #+#              #
#    Updated: 2024/05/10 22:58:04 by rrimonte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
LIBS_TARGET		:= 	libft/libft.a
HEADERS			=	pipex_bonus/pipex_bonus.h
SRCS			=	get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					pipex_bonus/ft_organize.c \
					pipex_bonus/ft_files_bonus.c \
					pipex_bonus/ft_lst_bonus.c \
					pipex_bonus/ft_exit.c \
					pipex_bonus/ft_pipes_bonus.c \
					pipex_bonus/pipes.c \
					pipex_bonus/here_docs.c \
					pipex_bonus/ft_child.c \
					free.c \
					pipex_bonus/main_bonus.c \
					builtins/env.c \
					builtins/echo.c \
					builtins/unset.c \
					builtins/get_env.c \
					builtins/pwd.c \
					builtins/shlvl.c \
					builtins/cd.c \
					builtins/cd_2.c \
					builtins/export.c \
					builtins/export2.c \
					builtins/exe_builtins.c \
					builtins/var_expansion.c \
					builtins/builtins_util.c \
					main.c \
					count_builtins.c \
					format_text.c \
					erase_quotes.c \
					exist_value.c \
					ft_count_quotes.c \
					init.c \
					split_cmd.c \
					check.c \
					check2.c \
					builtins/signal.c \
					utils.c
					
					

OBJS			=	$(SRCS:.c=.o)
CC				=	gcc
GET_NEXT_LINE_FOLDER	=	get_next_line/
LIBFT_FOLDER	=	libft/
LIBFT_NAME		=	libft.a
LIBS			=	$(LIBFT_FOLDER)$(LIBFT_NAME)
AR				=	ar rcs
CFLAGS			=	-Wall -Wextra -Werror -g #-fsanitize=address
RM				=	rm -rf

$(NAME): $(LIBS) $(OBJS) $(HEADERS)
		$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
$(LIBS_TARGET):
	$(MAKE) -C $(LIBFT_FOLDER)
all: $(NAME)
clean:
	$(MAKE) -C $(LIBFT_FOLDER) clean
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) -C $(LIBFT_FOLDER) fclean
	$(RM) $(NAME)
re: fclean all
