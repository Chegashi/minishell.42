#include<stdio.h>
#include<signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef struct s_pipes
{
    char *line;
    char **params;
	char **file;
	char **type;
	int inp;
	int out;
    struct s_pipes *next;
}               t_pipes;
typedef struct s_cmd{
    char *line;
    t_pipes *pipes;
    struct s_cmd *next;
}               t_cmd;

typedef struct s_shell
{
	char **envp;
	char ***cmd_list;
    struct s_cmd *cmd;
}       t_shell;
int g_fork = 0;
int	get_next_line(int fd, char **line);
/************* split_space ***********/
/************* join_path ***********/
char		*join_path(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == 0)
		return (NULL);
	while (s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '/';
	j++;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
/************* END join_path ***********/
static int	size_tab(char const *s)
{
	int count;
	int	i;
	int q;

	q = 0;
	i = 0;
	count = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != ' ') && s[i] != '\t')
			i++;
		count++;
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
	}
	return (count);
}

static int	size_word(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		i++;
	return (i);
}

static int	skip_word(char const *s)
{
	int i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	return (i);
}

static char	**free_table(char **tab, int j)
{
	while (j--)
		free(tab[j]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char		**splite_space(char const *s)
{
	char	**tab;
	size_t	i;
	size_t	count;
	count = size_tab(s);
	i = 0;
	if ((tab = (char**)malloc(sizeof(char*) * (count + 1))) == 0)
		return (NULL);
	while(*s == ' ' || *s == '\t')
		s++;
	while (i < count)
	{
		s = s + skip_word(s);
		if ((tab[i] = ft_substr(s, 0, size_word(s))) == 0)
			return (free_table(tab, i));
		i++;
		s = s + size_word(s);
	}
	tab[i] = NULL;
	return (tab);
}

/************* split_space ***********/
void ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}
int ft_prompt()
{
    ft_putstr("\e[1;32mminishell$ \e[0;37m");
    return (1);
}
char *get_line(char *line)
{
	char *tmp;
	int ret;

	tmp = ft_strdup("");
	line = NULL;
	while ((ret = get_next_line(0, &tmp)) >= 0)
	{
		if (line)
			line = ft_strjoin(line, tmp);
		else
			line = tmp;
		if (ret > 0)
			break ;
		else if (ret == 0 && !(*tmp) && !(*line))
		{
			ft_putstr("exit \n");
			exit(0);
		}
	}
	free(tmp);
	return (line);
}
int not_comp_quote(char *line)
{
	int i;

	int sngl;
	int dbl;

	i = 0;
	sngl = 0;
	dbl = 0;
	while (line[i])
	{
		if (line[i] == '\"' && dbl == 0 && sngl == 0)
			dbl = 1;
		else if (line[i] == '\"' && dbl == 1 && sngl == 0)
			dbl = 0;
		else if (line[i] == '\'' && dbl == 0 && sngl == 0)
			sngl = 1;
		else if (line[i] == '\'' && sngl == 1 && dbl == 0)
			sngl = 0;
		i++;
	}
	if (sngl == 1 || dbl == 1)
	{
		ft_putstr("Minishell: quote incomplete \n");
		return (-1);
	}
	return (0);
}
int ft_quote(char *line, int i)
{
	char quote;

	while (line[i] && (line[i] == '\'' || line[i] == '"'))
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (i == ((int) ft_strlen(line)))
			break;
		else
			i++;
	}
	return (i);
}
int ft_msgerr(char *line, char c, int i)
{	
	ft_putstr("Minishell: syntax error near unexpected token `");
	if (c == 'n')
		ft_putstr("newline");
	else if (line[i + 1] == c || (i > 0 && line[i - 1] == c))
	{
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
	}
	else
		ft_putchar_fd(c, 2);
	ft_putstr("'\n");
	return (-1);
}
int is_error(char *line, char c)
{
	int i;

	i = 1;
	if (line[0] == c)
		return (ft_msgerr(line, c, 0));
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '>' || line[i] == '<' || line[i] == c))
	{
		if (line[i] == c)
			return (ft_msgerr(line, c, i));
		i++;
	}
	while (line[i])
	{
		// check if the | in the quote if yes not return a error 
		if ((i = (ft_quote(line, i))) == (int)ft_strlen(line))
			break ;
		if (line[i] && line[i] == c)
		{
			while (line[++i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '>' || line[i] == '<' || line[i] == c))
			{
				if (line[i] == c)
					return (ft_msgerr(line, c, i));
			}
			if (line[i] == '\0')
				break;
		}
		i++;
	}
	return (0);
}



char *split_redirection(char *line)
{
	char *str;
	int i;
	int j;
	int q;

	q = 0;
	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	int size = ft_strlen(line) + 1;
	str = (char *)malloc(sizeof(char) * size);
	// if (check_redirection_error(line) == -1)
	// 	return (line);
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && !q)
			q = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && q)
			q = 0;
		if (((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '>')) && !q)
		{
			if (line[i - 1] && line[i - 1] != '>' &&  line[i - 1] != '<' && line[i - 1] != ' ')
			{
				size++;
				str = realloc (str, size);
				str[j++] = ' ';
			}
			str[j++] = line[i];
			str[j++] = line[i + 1];
			i++;
			if (line[i + 1] && line[i + 1] != '>' &&  line[i + 1] != '<' &&  line[i + 1] != ' ')
			{
				size++;
				str = realloc (str, size);
				str[j++] = ' ';
			}
		}
		else if ((line[i] == '>' || line[i] == '<') && !q)
		{
			if (line[i - 1] && line[i - 1] != '>' &&  line[i - 1] != '<' && line[i - 1] != ' ')
			{
				size++;
				str = realloc (str, size);
				str[j++] = ' ';
			}
			str[j++] = line[i];
			if (line[i + 1] && line[i + 1] != '>' &&  line[i + 1] != '<' &&  line[i + 1] != ' ')
			{
				size++;
				str = realloc (str, size);
				str[j++] = ' ';
			}
		}
		else
			str[j++] = line[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

/*
	- lets remove the file and the > from the line and store to ***file
	- check error function the first line and return the problem beside check the error of the ;
*/

int found_redirection(char *line)
{
    if (strcmp(line, ">") == 0 || strcmp(line, ">>") == 0|| strcmp(line, "<") == 0)  
        return (1);
    else
        return (0);
}
int count_redir(char **params)
{
	int i;
	int count;
	i = 0;
	count = 0;
	while (params[i])
	{
		if (found_redirection(params[i]))
			count++;
		i++;
	}
	return (count);
}
int check_not_qt(char **str, int pos)
{
	int i;
	int q;
	int j;

	i = 0;
	q = 0;

	while (i < pos)
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '\"' || str[i][j] == '\"') && !q)
				q = 1;
			else if ((str[i][j] == '\"' || str[i][j] == '\"') && q)
				q = 0;
			j++;
		}
		i++;
	}
	return (q);
}
int size_params(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void remove_params(t_pipes *pipes, int pos)
{
	int size;

	size = size_params(pipes->params);
	while (pos < size)
	{
		pipes->params[pos] = pipes->params[pos + 1];
		pos++;
	}
	pipes->params[pos + 1] = NULL;
    size--;
}

int found_in_useless(int *nb, int c)
{
	int i;
	
	i = 0;
	while (nb[i])
	{
		if (c == nb[i] || c == nb[i] + 1)
			return (1);
		i++;
	}
	return(0);
}
char **remove_useless(t_pipes *pipes, int *nb, int c)
{
	char **tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size_params(pipes->params) + 1));
	if (tmp == 0)
		return (pipes->params);
	while (pipes->params[i])
	{
		if (found_in_useless(nb, i) == 0)
		{
			tmp[j] = ft_strdup(pipes->params[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}
void ft_redirection(t_pipes *pipes)
{
	int i;
	int count;
	int j;
	int *nb_useless;
	j = 0;
	count = count_redir(pipes->params);
	i = 0;
	if ((pipes->file = (char **)malloc(sizeof(char *) * (count + 1))) == 0)
		return ;
	if ((pipes->type = (char **)malloc(sizeof(char *) * (count + 1))) == 0)
		return ;
	nb_useless  = (int *)malloc(sizeof(int *) * (count + 1));
	count = 0;
	while (pipes->params[i])
	{
		if (found_redirection(pipes->params[i]))
		{
			if (check_not_qt(pipes->params, i) == 0)
			{
				pipes->type[j] = ft_strdup(pipes->params[i]);
				nb_useless[j] = i;
				count++;
				if (pipes->params[i + 1])
				{
					pipes->file[j] = ft_strdup(pipes->params[i + 1]);
					count++;
				}
				else 
					pipes->file[j] = ft_strdup("");
				j++;
			}
		}
		i++;
	}
	pipes->file[j] = NULL;
	pipes->type[j] = NULL;
	pipes->params = remove_useless(pipes, nb_useless, count);
}
t_pipes *ft_multipipe(t_cmd *cmd_list, char *line)
{
    char **cmd;
    int i;
    t_pipes *tmp;

    cmd = ft_split(line, '|');
    if (cmd[0])
    {
        cmd_list->pipes = (t_pipes *)malloc(sizeof(t_pipes));
        cmd_list->pipes->line = split_redirection(cmd[0]);
        cmd_list->pipes->params = splite_space(cmd[0]);
		ft_redirection(cmd_list->pipes);
        i = 1;
        tmp = cmd_list->pipes;
        while (cmd[i])
        {
            tmp->next = (t_pipes *)malloc(sizeof(t_pipes));
            tmp = tmp->next;
            tmp->line = split_redirection(cmd[i]);
            tmp->params = splite_space(cmd[i]);
			ft_redirection(tmp);
            i++;
        }
        tmp->next = NULL;
    }
    else
        return (NULL);
    return (cmd_list->pipes);
}
t_pipes *fill_pipe(char *line)
{
    t_pipes *tmp;

    tmp = (t_pipes *)malloc(sizeof(t_pipes));
	if (tmp && line)
	{
		tmp->line = split_redirection(line);
        tmp->params = splite_space(tmp->line);
		ft_redirection(tmp);
		tmp->next = NULL;
	}
	else
		return(NULL);
	return (tmp);
}
t_pipes *stock_pipes(t_cmd *cmd, char *line)
{
    t_pipes *tmp;

    if (ft_strchr(line, '|'))
        tmp = ft_multipipe(cmd, line);
    else
        tmp = fill_pipe(line);
    return (tmp);
}
t_cmd *ft_mutlicmd(t_cmd *cmd_list, char *line)
{
    char **cmd;
    int i;
    t_cmd *tmp;

    cmd = ft_split(line, ';');
    if (cmd[0])
    {
        cmd_list = (t_cmd *)malloc(sizeof(t_cmd));
        cmd_list->line = cmd[0];
        cmd_list->pipes = NULL;
        i = 1;
        tmp = cmd_list;
        while (cmd[i])
        {
            tmp->next = (t_cmd *)malloc(sizeof(t_cmd));
            tmp = tmp->next;
            tmp->line = cmd[i];
            tmp->pipes = NULL;
            i++;
        }
        tmp->next = NULL;
    }
    else
        return (NULL);
    return (cmd_list);
}

t_cmd	*fill_cmd(t_cmd *tmp, char *line)
{
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (tmp && line)
	{
		tmp->line = line;
		tmp->pipes = NULL;
		tmp->next = NULL;
	}
	else
		return(NULL);
	return (tmp);
}


void print_pipes(t_pipes *pipe)
{
    t_pipes *cmd;
    int i;

    i = 0;
    cmd = pipe;
    while (cmd)
    {
        ft_putstr("pipe => |");
        ft_putstr(cmd->line);
        i = 0;
        ft_putstr("|\nparams => \n");
        while (cmd->params[i])
        {
            ft_putnbr_fd(i + 1, 1);
            ft_putstr("-> |");
            ft_putstr(cmd->params[i]);
            ft_putstr("|\n");
            i++;
        }
		i = 0;
		if (cmd->file)
		{
			ft_putstr("\nfile => \n");
			while (cmd->file[i])
			{
				ft_putnbr_fd(i + 1, 1);
				ft_putstr("-> |");
				ft_putstr(cmd->file[i]);
				ft_putstr("| -> |");
				ft_putstr(cmd->type[i]);
				//ft_putnbr_fd(cmd->out, 1);
				ft_putstr("|\n");
				i++;
			}
			ft_putstr("\n");
		}
        cmd = cmd->next;
    }
}
void print_list(t_shell *shell)
{
    t_cmd *tmp;

    tmp = shell->cmd;
    while (tmp)
    {
        ft_putstr("-----------------------------\n");
        ft_putstr("cmd => ");
        //ft_putstr(tmp->line);
        ft_putstr("\n");
        print_pipes(tmp->pipes);
        ft_putstr("-----------------------------\n");
        tmp = tmp->next;
    }
}

int parse_exterieur(int count)
{
	ft_putstr("minishell: ");
	ft_putstr("syntax error near unexpected token `");
	if (count >= 4)
		ft_putstr(">>'\n");
	else
		ft_putstr(">'\n");
	return (-1);
}
int parse_inferieur(int count)
{
	ft_putstr("minishell: ");
	ft_putstr("syntax error near unexpected token `");
	if (count > 5)
		ft_putstr("<<<'\n");
	else if (count > 4)
		ft_putstr("<<'\n");
	else
		ft_putstr("<'\n");
	return (-1);
}

int check_parse_redir(char *line, int start, int end)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (end > 0)
		line = ft_substr(line, start, end);
	if (strcmp(line, "<>") == 0)
	{
		ft_putstr("minishell: syntax error near unexpected token `<>'\n");
		return (-1);
	}
	if (!found_redirection(line))
	{
		while (line[i])
		{
			while (line[i] && line[i] == '>')
			{
				count++;
				i++;
			}
			if (count > 2)
				return (parse_exterieur(count));
			count = 0;
			while (line[i] && line[i] == '<')
			{
				count++;
				i++;
			}
			if (count > 1)
				return (parse_inferieur(count));
		}
	}
	return (0);
}
int no_file_dir(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : No such file or directory\n");
	return (-1);
}
int check_redi_filename(t_pipes *pipes)
{
	int i;

	i = 0;
	pipes->out = 0;
	pipes->inp = 0;
	while (pipes->type[i])
	{
		if (ft_strlen(pipes->file[i]) == 0)
		{
			ft_putstr("minishell: syntax error near unexpected token `newline'\n");
			return (-1);
		}
		if (found_redirection(pipes->file[i]))
		{
			if (check_parse_redir(pipes->file[i], 0, -1) == -1)
				return (-1);
			if (strcmp(pipes->file[i], ">") == 0)
				parse_exterieur(1);
			else if (strcmp(pipes->file[i], ">>") == 0)
				parse_exterieur(4);
			else if (strcmp(pipes->file[i], "<") == 0)
				parse_inferieur(1);
			return (-1);
		}
		if (strcmp(pipes->type[i], ">") == 0)
			pipes->out = open(pipes->file[i], O_CREAT | O_TRUNC | O_WRONLY , 0664);
		else if (strcmp(pipes->type[i], "<") == 0)
		{
			pipes->inp = open(pipes->file[i], O_RDONLY);
			if (pipes->inp < 0)
				return (no_file_dir(pipes->file[i]));
		}
		else if(strcmp(pipes->type[i], ">>") == 0)
			pipes->out = open(pipes->file[i],  O_CREAT | O_RDWR | O_APPEND, 0644);
		i++;
	}
	return (0);
}
int ft_pipes_redir(t_pipes *pipes)
{
	t_pipes *tmp;

	while (tmp)
	{
		if (check_redi_filename(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
int fill_pipes(t_cmd **cmd)
{
    t_cmd *tmp;

    tmp = *cmd;
    while (tmp)
    {
        tmp->pipes = stock_pipes(tmp, tmp->line);
		if (ft_pipes_redir(tmp->pipes) == -1)
			return (-1);
        tmp = tmp->next;
    }
	return (0);
}

int stock_command(t_cmd **cmd, char *line)
{
    if (ft_strchr(line, ';'))
        *cmd = ft_mutlicmd(*cmd, line);
    else
        *cmd = fill_cmd(*cmd, line);
    if (fill_pipes(cmd) == -1)
		return (-1);
	return (0);
}
int ft_cmdlen(t_pipes *pipes)
{
	t_pipes *tmp;
	int i;

	i = 0;
	tmp = pipes;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void not_found_folder(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : is a directory \n");
}
void excute_cmd(t_shell *shell, t_pipes *pipe)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(pipe->params[0], pipe->params , shell->envp);
	else if (pid < 0)
		ft_putstr("Fork failed \n");
	wait(&pid);
}

int check_command(char *s)
{
	if (strcmp(s, "echo") == 0 || strcmp(s, "ECHO") == 0 || strcmp(s, "cd") == 0 || strcmp(s, "CD") == 0  || strcmp(s, "pwd") == 0
		|| strcmp(s, "PWD") == 0 || strcmp(s, "export") == 0 || strcmp(s, "unset") == 0 || strcmp(s, "env") == 0 || strcmp(s, "ENV") == 0 || strcmp(s, "exit") == 0)
		return (1);
	return (0);
}
void ft_echo(t_shell *shell, t_pipes *pipe)
{
	ft_putstr(pipe->line);
	ft_putstr("\n");
}
void ft_cd(t_shell *shell, t_pipes *pipe)
{
	ft_putstr("cd running\n");
}
void ft_pwd(t_pipes *pipe)
{
	// check multi commands 
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr(cwd);
		ft_putstr("\n");
	}
}
void ft_export(t_shell *shell, t_pipes *pipe)
{
	ft_putstr("export running\n");
}
void ft_unset(t_shell *shell, t_pipes *pipe)
{
	ft_putstr("unset running\n");
}
void ft_env(t_shell *shell, t_pipes *pipe)
{
	ft_putstr("env running\n");
}

int ft_check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
// there is a problem in exiy
void ft_exit(t_shell *shell, t_pipes *pipe)
{
	ft_putstr("exit\n");
	exit(0);
}

int  search_path(char *line, t_pipes *pipe)
{
	char *path;
	char **all_path;
	struct stat stats;
	int i;
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = 0;
	while (all_path[i])
	{
		path = join_path(all_path[i], line);
		if (stat(path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
			{
				// here the update
				pipe->params[0] = ft_strdup(path);
				return (1);
			}
			else
				ft_putstr("permisison denied\n");
		}
		i++;
	}
	return (0);
}
void ft_path(t_shell *shell, char *path, t_pipes *pipe)
{
	struct stat stats;

	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			not_found_folder(path);
		else if (stats.st_mode && X_OK)
			excute_cmd(shell, pipe);
	}
	else
		no_file_dir(path);
}
void call_command(t_shell *shell, t_pipes *pipe, char *s)
{
	if (strcmp(s, "echo") == 0 || strcmp(s, "ECHO") == 0)
		ft_echo(shell, pipe);
	else if (strcmp(s, "cd") == 0 || strcmp(s, "CD") == 0)
		ft_cd(shell, pipe);
	else if (strcmp(s, "pwd") == 0 || strcmp(s, "PWD") == 0)
		ft_pwd(pipe);
	else if (strcmp(s, "export") == 0)
		ft_export(shell, pipe);
	else if (strcmp(s, "unset") == 0)
		ft_unset(shell, pipe);
	else if (strcmp(s, "env") == 0 || strcmp(s, "ENV") == 0)
		ft_env(shell, pipe);
	else if (strcmp(s, "exit") == 0)
		ft_exit(shell, pipe);
	else
		excute_cmd(shell, pipe);
}
void ft_not_found(char *cmd)
{
	ft_putstr("minishell: ");
	ft_putstr(cmd);
	ft_putstr(": command not found\n");
}
// void call_commands(t_shell *shell, t_pipes *pipe)
// {
// 	if (pipe->params[0])
// 	{
// 		if (pipe->params[0][0] == '/')
// 			ft_path(shell, pipe->params[0], pipe);
// 		else if (check_command(pipe->params[0]) == 0 && search_path(pipe->params[0], pipe) == 0)
// 				ft_not_found(pipe->params[0]);
// 		else 
// 			call_command(shell, pipe, pipe->params[0]);
// 	}
// }
void ft_pipes(t_shell *shell, t_cmd *cmd)
{
	t_pipes *tmp;

	int fd[2];
	pid_t pid;
	int fdd = 0;
	tmp = cmd->pipes;
	while (tmp)
	{
		if (tmp->params[0])
		{
			if (tmp->params[0][0] == '/')
			{
				ft_path(shell, tmp->params[0], tmp);
				break ;
			}
			else if (check_command(tmp->params[0]) == 0 && search_path(tmp->params[0], tmp) == 0 && found_redirection(tmp->params[0]) == 0)
			{
				ft_not_found(tmp->params[0]);
				break ;
			}
			else 
			{
				g_fork++;
				pipe(fd);
				pid = fork();
				if (pid == -1)
					exit(1);
				else if (pid == 0)
				{
					dup2(fdd, 0);
					if (tmp->next != NULL)
						dup2(fd[1], 1);
					close(fd[0]);
					if (tmp->out != 0)
					{
						dup2(tmp->out, 1);
						close(tmp->out);
					}
					if (tmp->inp != 0)
					{
						dup2(tmp->inp, 0);
						close(tmp->inp);
					}
					call_command(shell, tmp, tmp->params[0]);
					exit(1);
				}
				else 
				{
					wait(NULL);
					close(fd[1]);
					fdd = fd[0];
					tmp = tmp->next;
				}
			}
		}else
			tmp = tmp->next;
	}
}
void ft_excute(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		ft_pipes(shell, cmd);
		cmd = cmd->next;
	}
}

int is_redir_error(char *line)
{
	int i;
	int q;
	int end  = 0;
	int start  = 0;
	q = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !q)
			q = 0;
		else if ((line[i] == '\'' || line[i] == '\"') && q)
			q = 1;
		end = 0;
		start = i;
		while (line[i] && (line[i] == '>' || line[i] == '<'))
		{
			end++;
			i++;
		}
		if (start != i && check_parse_redir(line, start, end) == -1)
			return (-1);
		i++;
	}
	return (0);
}
void ft_free_all(t_shell *shell)
{
	// here to free everything
}
void ft_minishell(t_shell *shell)
{
    char	*line;
    line = (char *)malloc(sizeof(char *));
	while (ft_prompt())
	{
        line = get_line(line);
    	if (is_error(line, '|') == -1 || is_error(line, ';') == -1 || not_comp_quote(line) == -1 || is_redir_error(line) == -1)
			continue ;
        if (stock_command(&shell->cmd, line) == -1)
			continue ;
		ft_excute(shell);
        //print_list(shell);
	}
	free(line);
	line = NULL;
	ft_free_all(shell);
}
void signal_handler(int signum) 
{
  	if (signum == SIGINT)
	{
        ft_putstr("\n");
		ft_prompt();
	} 
  	else if (signum == SIGQUIT)
	{
		if (g_fork > 0)
			ft_putstr("Quit: 3\n");	
	}  
}

void ft_initialise(t_shell *shell, char **envp)
{
    shell->envp = envp;
    shell->cmd = NULL;
}
int main(int ac, char **av, char **envp)
{
    t_shell shell;
    ft_initialise(&shell, envp);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    ft_minishell(&shell);
}
