# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:36:34 by nbjaghou          #+#    #+#              #
#    Updated: 2021/07/28 13:25:57 by nbjaghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c 				\
 	  srcs/cmd_split.c 			\
 	  srcs/split_space.c 		\
	  srcs/split_redirection.c 	\
	  srcs/ft_excute.c 			\
	  srcs/ft_excute2.c 		\
	  srcs/ft_command.c 		\
	  srcs/search_path.c 		\
	  srcs/join_path.c 			\
	  srcs/call_command.c 		\
	  srcs/ft_echo.c 			\
	  srcs/ft_unset.c 			\
	  srcs/ft_cd.c 				\
	  srcs/ft_cd2.c 			\
	  srcs/ft_env.c 			\
	  srcs/ft_exit.c 			\
	  srcs/ft_export.c 			\
	  srcs/ft_export2.c 		\
	  srcs/ft_free.c 			\
	  srcs/ft_free2.c 			\
	  srcs/ft_heredoc.c 		\
	  srcs/ft_pwd.c 			\
	  srcs/ft_quote.c 			\
	  srcs/ft_quote2.c 			\
	  srcs/ft_redirection.c 	\
	  srcs/ft_redirection2.c 	\
	  srcs/ft_redirection3.c 	\
	  srcs/ft_replace.c 		\
	  srcs/remove_quote.c 		\
	  srcs/replace_variable.c	\
	  srcs/stock_command.c 		\
	  srcs/envp.c 				\
	  srcs/utils.c 				\
	  srcs/ft_unset2.c 			\
	  srcs/check_directory.c 	\
	  utils/ft_atoi.c			\
	  utils/ft_isprint.c		\
	  utils/ft_putchar_fd.c		\
	  utils/ft_putendl_fd.c		\
	  utils/ft_putstr_fd.c		\
	  utils/ft_split.c			\
	  utils/ft_strcmp.c			\
	  utils/ft_strdup.c			\
	  utils/ft_strjoin.c		\
	  utils/ft_substr.c			\
	  utils/ft_strchr.c			\
	  utils/ft_isdigit.c		\
	  utils/ft_strstr.c			\
	  utils/ft_memcpy.c			\
	  utils/ft_memset.c			\
	  utils/ft_itoa.c			\
	  utils/ft_strlen.c			\

OBJ = minishell.o \
 	  srcs/cmd_split.o 			\
 	  srcs/split_space.o 		\
	  srcs/split_redirection.o 	\
	  srcs/ft_excute.o 			\
	  srcs/ft_excute2.o 		\
	  srcs/ft_command.o 		\
	  srcs/search_path.o 		\
	  srcs/join_path.o 			\
	  srcs/call_command.o 		\
	  srcs/ft_echo.o 			\
	  srcs/ft_replace.o 		\
	  srcs/ft_unset.o 			\
	  srcs/ft_cd.o 				\
	  srcs/ft_cd2.o 			\
	  srcs/ft_env.o 			\
	  srcs/ft_exit.o 			\
	  srcs/ft_export.o 			\
	  srcs/ft_export2.o 		\
	  srcs/ft_free.o 			\
	  srcs/ft_free2.o 			\
	  srcs/ft_heredoc.o 		\
	  srcs/ft_pwd.o 			\
	  srcs/ft_quote.o 			\
	  srcs/ft_quote2.o 			\
	  srcs/ft_redirection.o 	\
	  srcs/ft_redirection2.o 	\
	  srcs/ft_redirection3.o 	\
	  srcs/check_directory.o 	\
	  srcs/remove_quote.o 		\
	  srcs/replace_variable.o	\
	  srcs/stock_command.o 		\
	  srcs/envp.o 				\
	  srcs/ft_unset2.o 			\
	  srcs/utils.o 				\
	  utils/ft_atoi.o			\
	  utils/ft_isprint.o		\
	  utils/ft_putchar_fd.o		\
	  utils/ft_putendl_fd.o		\
	  utils/ft_putstr_fd.o		\
	  utils/ft_split.o			\
	  utils/ft_strcmp.o			\
	  utils/ft_strdup.o			\
	  utils/ft_strjoin.o		\
	  utils/ft_substr.o			\
	  utils/ft_strchr.o			\
	  utils/ft_isdigit.o		\
	  utils/ft_strstr.o			\
	  utils/ft_memcpy.o			\
	  utils/ft_memset.o			\
	  utils/ft_itoa.o			\
	  utils/ft_strlen.o			\

FLAGS = -Wall -Wextra -Werror

USER=nbjaghou

TERMFLAG = -lreadline

all : $(NAME)

$(NAME) : ${OBJ}
	gcc -o $(NAME) ${OBJ} ${TERMFLAG} ${FLAGS}

.c.o : ${SRC}
	gcc -c $< -o ${<:.c=.o}

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all