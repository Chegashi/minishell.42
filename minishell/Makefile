# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:36:34 by nbjaghou          #+#    #+#              #
#    Updated: 2021/07/02 16:14:09 by mochegri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c \
	  srcs/call_command.c \
	  srcs/check_redi_filename.c \
	  srcs/cmd_split.c 		\
	  srcs/ft_cd.c 			\
	  srcs/ft_command.c 	\
	  srcs/ft_echo.c 		\
	  srcs/ft_env.c 		\
	  srcs/ft_excute.c 		\
	  srcs/ft_exit.c 		\
	  srcs/ft_export.c 		\
	  srcs/ft_free.c 		\
	  srcs/ft_free2.c 		\
	  srcs/ft_pipes.c 		\
	  srcs/ft_prompt.c 		\
	  srcs/ft_pwd.c 		\
	  srcs/ft_redirection.c \
	  srcs/ft_redirection2.c \
	  srcs/ft_signal.c 		\
	  srcs/ft_unset.c 		\
	  srcs/hist_utils.c 	\
	  srcs/is_error.c 		\
	  srcs/is_redir_error.c \
	  srcs/join_path.c 		\
	  srcs/not_comp_quote.c \
	  srcs/split_redirection.c \
	  srcs/split_space.c 	\
	  srcs/stock_cmd.c 		\
	  srcs/term_utils.c 	\
	  srcs/termcap.c 		\
	  srcs/termcap2.c 		\
	  srcs/utils.c 			\
  	  srcs/search_path.c	\
	  utils/ft_atoi.c		\
	  utils/ft_isprint.c	\
	  utils/ft_putchar_fd.c	\
	  utils/ft_putendl_fd.c	\
	  utils/ft_putstr_fd.c	\
	  utils/ft_split.c		\
	  utils/ft_strcmp.c		\
	  utils/ft_strncmp.c	\
	  utils/ft_strdup.c		\
	  utils/ft_strjoin.c	\
	  utils/ft_strlen.c		\
	  utils/ft_substr.c		\
	  

OBJ = minishell.o \
	  srcs/call_command.o \
	  srcs/check_redi_filename.o \
	  srcs/cmd_split.o 		\
	  srcs/ft_cd.o 			\
	  srcs/ft_command.o 	\
	  srcs/ft_echo.o 		\
	  srcs/ft_env.o 		\
	  srcs/ft_excute.o 		\
	  srcs/ft_exit.o 		\
	  srcs/ft_export.o 		\
	  srcs/ft_free.o 		\
	  srcs/ft_free2.o 		\
	  srcs/ft_pipes.o 		\
	  srcs/ft_prompt.o 		\
	  srcs/ft_pwd.o 		\
	  srcs/ft_redirection.o \
	  srcs/ft_redirection2.o \
	  srcs/ft_signal.o 		\
	  srcs/ft_unset.o 		\
	  srcs/hist_utils.o 	\
	  srcs/is_error.o 		\
	  srcs/is_redir_error.o \
	  srcs/join_path.o 		\
	  srcs/not_comp_quote.o \
	  srcs/split_redirection.o \
	  srcs/split_space.o 	\
	  srcs/stock_cmd.o 		\
	  srcs/term_utils.o 	\
	  srcs/termcap.o 		\
	  srcs/termcap2.o 		\
	  srcs/utils.o 			\
	  srcs/search_path.o	\
	  utils/ft_atoi.o		\
	  utils/ft_isprint.o	\
	  utils/ft_putchar_fd.o	\
	  utils/ft_putendl_fd.o	\
	  utils/ft_putstr_fd.o	\
	  utils/ft_split.o		\
	  utils/ft_strcmp.o		\
	  utils/ft_strncmp.o	\
	  utils/ft_strdup.o		\
	  utils/ft_strjoin.o	\
	  utils/ft_strlen.o		\
	  utils/ft_substr.o		\

FLAGS = -Wall -Wextra -Werror 

TERMFLAG = -ltermcap

all : $(NAME)

$(NAME) : ${OBJ}
	gcc -g -o $(NAME) ${OBJ} ${FLAGS}  ${TERMFLAG}

.c.o : ${SRC}
		gcc -c $< -o ${<:.c=.o}

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all