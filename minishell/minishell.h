/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:27:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/02 19:41:27 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <term.h>
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define ENTER_ARROW 10
# define BUFFER_SIZE 2048
# define CTRLD 4
# define BACKSPACE 127
int	g_fork = 0;
// typedef struct s_history
// {
// 	char				*line;
// 	struct s_history	*prev;
// 	struct s_history	*next;
// }				t_hist;
typedef struct s_pipes
{
	char				*line;
	char				**params;
	char				**file;
	char				**type;
	int					inp;
	int					out;
	struct s_pipes		*next;
}				t_pipes;
typedef struct s_cmd
{
	char				*line;
	t_pipes				*pipes;
	struct s_cmd		*next;
}				t_cmd;
typedef struct s_shell
{
	char				**envp;
	struct s_cmd		*cmd;
	t_list				*hist;
	int					col;
	int					row;
	int					new_col;
	char				*line;
	int					fork;
}				t_shell;
#endif