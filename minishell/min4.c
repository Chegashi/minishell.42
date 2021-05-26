#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
//Used for handling directory files
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
// typedef struct s_simple_cmd
// {
//     char    *line;
//     char    **params;
//     struct s_simple_cmd *next;
// }               t_simple_cmd;
typedef struct s_pipes
{
    char *line;
    char **params;
    struct s_pipes *next;
}               t_pipes;
typedef struct s_cmd{
    char *line;
    t_pipes *pipes;
	// t_redirection *redirection;
    struct s_cmd *next;
}               t_cmd;

typedef struct s_shell
{
	char **envp;
	char ***cmd_list;
    struct s_cmd *cmd;
	int count_pipes;
}       t_shell;

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

	i = 0;
	count = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != ' ' && s[i] != '\t')
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
t_pipes *ft_multipipe(t_cmd *cmd_list, char *line)
{
    char **cmd;
    int i;
    t_pipes *tmp;

    cmd = ft_split(line, '|');
    if (cmd[0])
    {
        cmd_list->pipes = (t_pipes *)malloc(sizeof(t_pipes));
        cmd_list->pipes->line = cmd[0];
        cmd_list->pipes->params = splite_space(cmd[0]);
        i = 1;
        tmp = cmd_list->pipes;
        while (cmd[i])
        {
            tmp->next = (t_pipes *)malloc(sizeof(t_pipes));
            tmp = tmp->next;
            tmp->line = cmd[i];
            tmp->params = splite_space(cmd[i]);
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
		tmp->line = line;
        tmp->params = splite_space(line);
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
        ft_putstr("\n");
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
        ft_putstr(tmp->line);
        ft_putstr("\n");
        print_pipes(tmp->pipes);
        ft_putstr("-----------------------------\n");
        tmp = tmp->next;
    }
}
int found_redirection(char *line)
{
    if (strcmp(line, ">") || strcmp(line, ">>") || strcmp(line, "<"))  
        return (1);
    else
        return (0);
}

void fill_pipes(t_cmd **cmd)
{
    t_cmd *tmp;

    tmp = *cmd;
    while (tmp)
    {
        tmp->pipes = stock_pipes(tmp, tmp->line);
        tmp = tmp->next;
    }
}

void stock_command(t_cmd **cmd, char *line)
{
    if (ft_strchr(line, ';'))
        *cmd = ft_mutlicmd(*cmd, line);
    else
        *cmd = fill_cmd(*cmd, line);
    fill_pipes(cmd);
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
void no_file_dir(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : No such file or directory\n");
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
void call_commands(t_shell *shell, t_pipes *pipe)
{
	if (pipe->params[0])
	{
		if (pipe->params[0][0] == '/')
			ft_path(shell, pipe->params[0], pipe);
		else if (check_command(pipe->params[0]) == 0 && search_path(pipe->params[0], pipe) == 0)
				ft_not_found(pipe->params[0]);
		else 
			call_command(shell, pipe, pipe->params[0]);
	}
}
void ft_pipes(t_shell *shell, t_cmd *cmd)
{
	t_pipes *tmp;

	int fd[2];
	pid_t pid;
	int fdd = 0;
	tmp = cmd->pipes;
	while (tmp)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			ft_putstr("fork problem");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (tmp->next != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			call_commands(shell, tmp);
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
void ft_minishell(t_shell *shell)
{
    char	*line;
    line = (char *)malloc(sizeof(char *));
	while (ft_prompt())
	{
        line = get_line(line);
    	if (is_error(line, '|') == -1 || is_error(line, ';') == -1 || not_comp_quote(line) == -1)
			continue ;
        stock_command(&shell->cmd, line);
		ft_excute(shell);
        //print_list(shell);
	}
	free(line);
	line = NULL;
}
void signal_handler(int signum) 
{
  	if (signum == SIGINT)
	{
        ft_putstr("\n");
		ft_prompt();
		signal(SIGINT, signal_handler);
	} 
  	else if (signum == SIGQUIT)
	{
        ft_putstr("Quit: 3");
        ft_putstr("\n");
	}  
}

void ft_initialise(t_shell *shell, char **envp)
{
    shell->envp = envp;
    shell->cmd = NULL;
	shell->count_pipes = 0;
}
int main(int ac, char **av, char **envp)
{
    t_shell shell;
    ft_initialise(&shell, envp);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    ft_minishell(&shell);
}