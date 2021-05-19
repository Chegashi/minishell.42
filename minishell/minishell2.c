
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
//Used for handling directory files
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"

/***
 * 
 * to DO :
 * 		- pipes (found a solution)
 * 		- redirections
 * 		- echo
 * 		- cd
 * 		- export 
 * 		- unset
 * 		- $? (Shows the exit status of the last command
 *		- variable 
*		- history with termcap
*		- ctrl + d / ctrl + \ handler
*		- path of command excute too  (/bin/ls) // done
*		lets add a type of every command to see if it have the pipes so we can do special execute
*		see if we need to excute the func maked in the directory as /bin/echo // yes not oblg 

 */
int	get_next_line(int fd, char **line);

typedef struct s_cmd
{
    char **cmd;
	// t_pipes *pipes;
    struct s_cmd *next;
}       t_cmd;

typedef struct s_shell
{
	char **envp;
    struct s_cmd *cmd;
}       t_shell;
/************* split_space ***********/
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
void ft_initialise(t_shell *shell, char **envp)
{
    shell->envp = envp;
    shell->cmd = NULL;
}

void ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

void ft_prompt()
{
    ft_putstr("\e[1;32mminishell$ \e[0;37m");
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

t_cmd *ft_mutlicmd(t_shell *shell, char *line)
{
    char **cmd;
    int i;
    t_cmd *tmp;

    cmd = ft_split(line, ';');
    tmp = shell->cmd;
    if (cmd[0])
    {
        shell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
        shell->cmd->cmd = splite_space(cmd[0]);
        i = 1;
        tmp = shell->cmd;
        while (cmd[i])
        {
            tmp->next = (t_cmd *)malloc(sizeof(t_cmd));
            tmp = tmp->next;
            tmp->cmd = splite_space(cmd[i]);
            i++;
        }
        tmp->next = NULL;
    }
    else
        return (NULL);
    return (shell->cmd);
}

t_cmd	*fill_cmd(char *line)
{
	t_cmd *tmp;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (tmp && line)
	{
		tmp->cmd = splite_space(line);
		tmp->next = NULL;
	}
	else
		return(NULL);
	return (tmp);
}

void print_list(t_shell *shell)
{
	t_cmd *tmp;

	tmp = shell->cmd;
	int i = 0;
	while (tmp)
	{
		ft_putstr("cmd: ");
		i = 0;
		while (tmp->cmd[i])
		{
			ft_putstr(tmp->cmd[i]);
			ft_putstr("   ");
			i++;
		}
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

t_cmd *stock_command(t_shell *shell, char *line)
{
    t_cmd *tmp;
    char *check;
    if (ft_strchr(line, ';'))
        tmp = ft_mutlicmd(shell, line);
    else
        tmp = fill_cmd(line);
    return (tmp);
}

int ft_msgerr(char *line, char c, int i)
{	
	ft_putstr("minishell: syntax error near unexpected token `");
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
int check_command(char *s)
{
	if (strcmp(s, "echo") == 0 || strcmp(s, "cd") == 0 || strcmp(s, "pwd") == 0
		|| strcmp(s, "export") == 0 || strcmp(s, "unset") == 0 || strcmp(s, "env") == 0 || strcmp(s, "exit") == 0)
		return (1);
	return (0);
}
void ft_not_found(char *cmd)
{
	ft_putstr("minishell: ");
	ft_putstr(cmd);
	ft_putstr(": command not found\n");
}
int  search_path(char *line, t_cmd *cmd)
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
				cmd->cmd[0] = ft_strdup(path);
				return (1);
			}
			else
				ft_putstr("permisison denied\n");
		}
		i++;
	}
	return (0);
}
void ft_echo(t_shell *shell)
{

}
void ft_cd(t_shell *shell)
{

}
void ft_pwd(t_shell *shell)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr(cwd);
		ft_putstr("\n");
	}
}
void ft_export(t_shell *shell)
{

}
void ft_unset(t_shell *shell)
{

}
void ft_env(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->cmd->cmd[1])
	{
		ft_putstr("env: '");
		ft_putstr(shell->cmd->cmd[1]);
		ft_putstr("': No such file or directory\n");
	}
	else{
		while (shell->envp[i])
		{
			ft_putstr(shell->envp[i]);
			ft_putstr("\n");
			i++;
		}
	}

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
void ft_exit(t_shell *shell)
{
	char **tmp;
	int i;

	tmp = shell->cmd->cmd;
	i = 0;
	while (tmp[i])
		i++;
	ft_putstr("exit\n");
	if (shell->cmd->cmd[1] && !ft_check_digit(shell->cmd->cmd[1]))
	{
		ft_putstr("minishell: exit: ");
		ft_putstr(shell->cmd->cmd[1]);
		ft_putstr(" : numeric argument required\n");
		exit(0);
	}
	else if (i > 2)
		ft_putstr("exit: too many arguments \n");
	else if (i == 2 && shell->cmd->cmd[1] && ft_check_digit(shell->cmd->cmd[1]))
	{
		exit(ft_atoi(shell->cmd->cmd[1]));
	}
	exit(0);
}

void excute_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(cmd->cmd[0], cmd->cmd , shell->envp);
	else if (pid < 0)
		ft_putstr("Fork failed \n");
	wait(&pid);
}


void ft_excute(t_shell *shell, char **s)
{
	if (strcmp(s[0], "echo") == 0)
		ft_echo(shell);
	else if (strcmp(s[0], "cd") == 0)
		ft_cd(shell);
	else if (strcmp(s[0], "pwd") == 0)
		ft_pwd(shell);
	else if (strcmp(s[0], "export") == 0)
		ft_export(shell);
	else if (strcmp(s[0], "unset") == 0)
		ft_unset(shell);
	else if (strcmp(s[0], "env") == 0)
		ft_env(shell);
	else if (strcmp(s[0], "exit") == 0)
		ft_exit(shell);
	else
		excute_cmd(shell, shell->cmd);
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
		ft_putstr("minishell: quote incomplete \n");
		return (-1);
	}
	return (0);
}

int is_path(t_shell *shell, char *path, t_cmd *cmd)
{
	struct stat stats;
	int i;

	i = 0;
	if (path[0] == '/')
	{
		if (stat(path, &stats) == 0)
		{
			if (stats.st_mode && X_OK)
			{
				excute_cmd(shell, cmd);
				return (1);
			}
			else{
				ft_putstr("what hell here");
			}
		}
	}
	return (0);
}
void not_found_folder(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : is a directory \n");
}
void no_file_dir(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : No such file or directory\n");
}
void ft_path(t_shell *shell, char *path)
{
	struct stat stats;

	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			not_found_folder(path);
		else if (stats.st_mode && X_OK)
			excute_cmd(shell, shell->cmd);
	}
	else
		no_file_dir(path);
}
// check if the path is true add todo
void check_commands(t_shell *shell, char *line)
{
	t_cmd *tmp;

	tmp = shell->cmd;
	if (is_error(line, '|') == -1 || is_error(line, ';') == -1 || not_comp_quote(line) == -1)
		return ;
	while (tmp)
	{
		// maybe here the seg check in search_path +add 
		if (tmp->cmd[0]){
			if (tmp->cmd[0][0] == '/')
				ft_path(shell, tmp->cmd[0]);
			else if (check_command(tmp->cmd[0]) == 0 && search_path(tmp->cmd[0], tmp) == 0)
				ft_not_found(tmp->cmd[0]);
			else
				ft_excute(shell, tmp->cmd);
		}
		tmp = tmp->next;
	}
}

void ft_minishell(t_shell *shell)
{
    char	*line;
    line = (char *)malloc(sizeof(char *));
	while (get_next_line(0, &line))
	{
        shell->cmd = stock_command(shell, line);
        check_commands(shell, line);
		ft_prompt();
	}
	free(line);
	line = NULL;
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;
    ft_initialise(&shell, envp);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    ft_prompt();
    ft_minishell(&shell);
}