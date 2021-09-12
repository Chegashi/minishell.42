/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:27:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:26:42 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include "utils/utils.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# define MAX_PATH 4096
typedef struct s_mem
{
	char				*line;
	struct s_mem		*next;
}				t_mem;
typedef struct s_data
{
	char				*line;
	int					done;
	char				**envp;
	struct s_cmd		*cmd;
	int					fork;
	pid_t				pid;
	int					*pipes[2];
	int					*status;
	int					*pids;
	int					n_cmd;
	int					n_pi;
	int					stdin_cpy;
	int					ctrl_c;
	char				buf[255];
	t_mem				*mem;
	int					n_exit;
	int					error;
	char				*pwd;
}				t_data;

typedef struct s_pipes
{
	char				*line;
	char				**params;
	int					inp;
	int					out;
	char				**file;
	char				**type;
	int					*nb_useless;
	char				*str;
	struct s_pipes		*next;
}				t_pipes;
typedef struct s_cmd
{
	char				*line;
	t_pipes				*pipes;
	struct s_cmd		*next;
}				t_cmd;
typedef struct s_split
{
	char	*str;
	int		i;
	int		j;
	int		q;
}				t_split;
typedef struct s_replace
{
	char	*tmp;
	char	*new;
	char	*old;
	int		old_l;
	int		sub_l;
	int		rp_l;
}				t_replace;

t_data	g_data;
char	**cmd_split(char const *s, char c);
char	**free_table(char **tabl, int j);
char	**splite_space(char const *s);
char	*split_redirection(char *line);
void	ft_excute(void);
int		count_pipes(t_pipes *pipes);
char	*join_path(char const *s1, char const *s2);
int		found_redirection(char *line);
void	ft_putstr(char *line);
int		search_path(char *line, t_pipes *pipe, char *pt);
int		check_error_cmd(t_pipes *pipe);
void	add_to_mem(t_mem **mem, char *line);
void	call_command(t_pipes *pipe, char *s);
void	ft_exit(t_pipes *pipe);
void	ft_echo(t_pipes *pipe);
void	ft_cd(char **params);
char	*str_replace(char *str, char *sub, char *replace);
void	ft_unset(char **params);
void	free_ta(char **tabl);
void	ft_env(void);
int		ft_builtins(t_pipes *pipe);
int		env_size(char **params);
char	*value_from_str(char *str);
char	*key_from_str(char *str);
int		ft_strlen_dil(char *str, char d);
int		check_command(char *s);
char	*remove_quote(char *line, int i, int j);
char	*replace_variable(char *line);
void	stock_pipes(t_cmd **cmd);
void	add_to_env(char *str, char **envp);
int		edit_envp(char *var, char *str);
int		search_env(char *str);
int		ft_isalpha(int c);
char	*change_plus_envp(char *str);
void	init_envp(char **envp);
void	ft_pwd(void);
void	ft_export(t_pipes *pipe, int i);
int		not_comp_quote(char *line);
int		quote_error(void);
int		is_error(char *line, char c, int i);
int		ft_quote(char *line, int i);
int		is_error_help(char *line, int i, char c);
int		end_semi_file(char *line, int i);
int		end_pipe_file(char *line, int i);
int		msg_error(char *line, char c, int i);
void	ft_heredoc(char *name);
int		no_file_dir(char *s);
char	**remove_useless(t_pipes *pipes, int *nb);
int		found_in_useless(int *nb, int c);
void	ft_redirection(t_pipes *pipes);
int		check_redi_filename(t_pipes *pipes, int i);
int		check_redi_filehelper(char **file, int i);
int		check_redi_file2(t_pipes *pipes, int i);
void	ft_redir_helper(t_pipes *pipes, int i, int j);
int		check_not_qt(char **str, int pos);
int		is_redir_error(char *line);
int		count_redir(char **params);
int		check_redi_errors(char *line, int start, int nb_red);
int		error_count_redirection(char *line);
int		check_redir(char *line, int i, int *count);
int		parse_inferieur(int count);
int		parse_exterieur(int count);
int		stock_command(t_cmd **cmd, char *line);
void	add_cmd_list(t_cmd **cmd, char *line);
void	add_pipe_list(t_pipes **pipe, char *line);
char	**change_params(char *line);
char	*get_variable(char *var);
void	ft_free(char *line);
void	clear_data(void);
void	free_list(t_cmd *cmd);
void	free_pipes(t_pipes *pipes);
int		count_tabl(char **tabl);
void	clear_mem(void);
int		check_space(char c);
int		export_str_error(char *str);
void	read_export(char **envp);
void	msg_error_export(char *msg, char *str);
void	ft_pipe(t_pipes *cmd, int i, int p[g_data.n_pi][2]);
int		check_directory(char *cmd);
void	error_no_file(char *cmd);
void	error_is_dir(char *cmd);
void	add_pwd(char *key, char *pwd);
#endif