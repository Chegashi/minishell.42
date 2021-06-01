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
#include <termios.h>
#include <curses.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <term.h>
#define UP_ARROW 4283163
#define DOWN_ARROW 4348699
#define ENTER_ARROW 10
#define BUFFER_SIZE 2048
#define CTRLD 4
typedef struct s_history
{
    char *line;
    struct s_history *prev;
    struct s_history *next;
}               t_hist;
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
    struct s_cmd *cmd;
	t_hist *hist;
    int col;
    char *line;
}       t_shell;


void ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}
int ft_prompt()
{
    ft_putstr("\e[1;32mminishell$ \e[0;37m");
    return (1);
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
		ft_putstr("Quit: 3\n");	
	}  
}

int putchar_term(int c)
{
    return (write(1, &c, 1));
}

void ft_ctrld()
{
    ft_putstr("exit\n");
    exit(0);
}
void ft_arrow_up(t_shell *shell)
{
    tputs(restore_cursor, 1, putchar_term);
    tputs(tgetstr("ce", NULL), 1, putchar_term);
    ft_putstr("\n");
}
void ft_arrow_down(t_shell *shell)
{
    tputs(restore_cursor, 1, putchar_term);
    tputs(tgetstr("ce", NULL), 1, putchar_term);
    write(1, "next", 5);
}
void	add_hist_list(t_hist **hist, t_hist *tmp)
{
	if (*hist)
	{
		tmp->next = *hist;
		(*hist)->prev = tmp;
		*hist = tmp;
	}
	else
		*hist = tmp;
}
void add_to_history(t_shell *shell, char *line)
{
	t_hist *tmp;

	if(!line)
		return ;
	tmp = (t_hist *)malloc(sizeof(t_hist));
	if (!tmp)
		return ;
	tmp->line = ft_strdup(line);
	add_hist_list(&shell->hist, tmp);
}

void ft_arrow_enter(t_shell *shell, int i)
{
    shell->line[i] = '\0';
    ft_putstr("\n");
    shell->col++;
    add_to_history(shell, shell->line);
    ft_prompt();
}
void read_line(t_shell *shell)
{
    int c;
    int i;

    i = 0;
    while (read(0, &c, sizeof(c)) >= 0)
    {
        if (c == CTRLD)
            ft_ctrld();
        else if (c == UP_ARROW)
            ft_arrow_up(shell);
        else if (c == DOWN_ARROW)
            ft_arrow_down(shell);
        else if (c == ENTER_ARROW)
        {
            ft_arrow_enter(shell, i);
            i = 0;
        }
        else
        {
            shell->line[i] = c;
            i++;
            write(1, &c, 1);
        }
        c = 0;
    }
}
void ft_minishell(t_shell *shell)
{
    struct termios term;
    char *term_name;
    int c;
    int i;

    term_name = getenv("TERM");
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
    tgetent(0, term_name); 
    tputs(save_cursor, 1, putchar_term);
    read_line(shell);
}
void ft_initialise(t_shell *shell, char **envp)
{
    shell->envp = envp;
    shell->cmd = NULL;
    shell->hist = NULL;
    shell->line = (char *)malloc(sizeof(char));
    shell->col = 0;
}
int main(int ac, char **av, char **envp)
{
    t_shell shell;
    ft_initialise(&shell, envp);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    ft_prompt();
    ft_minishell(&shell);
    return (0);
}