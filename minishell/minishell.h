/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:27:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/02 16:04:35 by mochegri         ###   ########.fr       */
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
# include "utils/utils.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <term.h>
# define BUFFER_SIZE 2048
# define BACKSPACE 127
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define ENTER_ARROW 10
# define CTRLD 4

typedef struct		s_v_env
{
    char			*key;
    char			*value;
    struct s_v_env	*next;
}					t_v_env;

typedef struct	s_data
{
	int			fork;
}				t_data;

typedef struct s_hist
{
	char				*line;
	struct s_hist		*prev;
	struct s_hist		*next;
}				t_hist;

typedef struct s_pipes
{
	char				*line;
	char				**params;
	char				**file;
	char				**type;
	int					*nb_useless;
	int					inp;
	int					out;
	int					is_red;
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
	t_v_env				*envp;
	struct s_cmd		*cmd;
	t_hist				*hist;
	t_hist				*hist_last;
	int					fork;
	char				*line;
	int					enter;
	struct termios		orig_term;
	pid_t				pid;
	int					*pipes[2];
	int					*status;
	int					*pids;
	int					n_cmd;
	int					n_pi;
	int					c;
	char				buf[255];
}				t_shell;

typedef struct s_split
{
	char	*str;
	int		i;
	int		j;
	int		q;
}				t_split;

t_data	g_data;
t_v_env *init_envp(char **envp);
void	ft_putstr(char *str);
int		ft_prompt(void);
void	signal_handler(int signum);
char	*get_line(t_shell *shell, char *line);
int		get_next_line(int fd, char **line);
int		ft_quote(char *line, int i);
int		msg_error(char *line, char c, int i);
int		is_error(char *line, char c);
int		is_redir_error(char *line);
int		found_redirection(char *line);
int		parse_inferieur(int count);
int		parse_exterieur(int count);
int		check_parse_redir(char *line, int start, int end);
int		not_comp_quote(char *line);
int		stock_command(t_cmd **cmd, char *line);
int		fill_pipes(t_cmd *cmd);
void	print_list(t_cmd *cmd);
char	**cmd_split(char const *s, char c);
char	**splite_space(char const *s);
char	*split_redirection(char *line);
void	ft_redirection(t_pipes *pipes);
void	ft_redir_helper(t_pipes *pipes, int i, int *count, int j);
char	**remove_useless(t_pipes *pipes, int *nb);
int		found_in_useless(int *nb, int c);
int		check_redi_filename(t_pipes *pipes);
int		no_file_dir(char *s);
int		ft_pipes_redir(t_pipes *pipes);
char	**free_table(char **tabl, int j);
int		skip_space(char const *s, int i);
int		check_space(char c);
int		check_redir(char *line, int i, int *count);
void	ft_free(char *line);
void	free_list(t_cmd *cmd);
void	free_hist(t_hist *hist);
void	clear_data(t_shell *shell);
int		count_tabl(char **tabl);
t_hist	*ft_histnew(char *line);
void	ft_histadd_front(t_hist **alst, t_hist *new);
int		ft_histsize(t_hist *lst);
t_hist	*ft_histlast(t_hist *lst);
int		putchar_term(int c);
int		nbr_length(int n);
void	delete_end(t_shell *shell, int *col, int *row);
void	get_cursor_position(t_shell *shell, int *col, int *rows);
void	join_char(t_shell *shell, int c, int *col);
void	ft_arrow_up(t_shell *shell, int c, int *col);
void	ft_arrow_down(t_shell *shell, int c, int *col);
void	read_line(t_shell *shell);
void	ft_minishell_help(t_shell *shell);
void	ft_enter_line(t_shell *shell);
void	ft_ctrld(t_shell *shell);
void	add_to_history(t_shell *shell);
char	*join_path(char const *s1, char const *s2);
int		check_command(char *s);
int		search_path(char *line, t_pipes *pipe);
void	ft_not_found(char *cmd);
int		check_error_cmd(t_pipes *pipe);
void	ft_excute(t_shell *shell);
void	excute_pipes(t_shell *shell, t_cmd *cmd);
void	call_command(t_shell *shell, t_pipes *pipe, char *s);
void	ft_cd(t_shell *shell, t_pipes *pipe);
void	ft_echo(t_v_env *head, t_pipes *pipe);
void	ft_env(t_v_env *head);
void	ft_exit(t_shell *shell, t_pipes *pipe);
void	ft_export(t_shell *shell, t_pipes *pipe);
void	ft_pwd(t_pipes *pipe);
void	ft_unset(t_shell *shell, t_pipes *pipe);
int		count_redir(char **params);
int		check_not_qt(char **str, int pos);
int		size_params(char **str);
void	remove_params(t_pipes *pipes, int pos);
void	free_ta(char **tabl);
int		count_pipes(t_pipes *pipes);


char	*key_from_str(char *str);
t_v_env	*str_to_v_env(char *str);
char	*value_from_str(char *str);
char	*key_from_str(char *str);
int	ft_strlen_dil(char *str, char d);
t_v_env	*init_envp(char **envp);
char	*get_value(char *key, t_v_env *head);

#endif