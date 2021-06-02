#include "minishell.h"

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

int 	ft_prompt(void)
{
	ft_putstr("\e[1;32mminishell$ \e[0;37m");
	return (1);
}

void	signal_handler(int signum)
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

int 	putchar_term(int c)
{
	return (write(1, &c, 1));
}
void print_hist(t_shell *shell)
{
	t_list *tmp;

	tmp = shell->hist;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
}
void	ft_ctrld(t_shell *shell)
{
	ft_putstr("exit\n");
	print_hist(shell);
	exit(0);
}
int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}
char *line_hist(t_shell *shell)
{
	int i;
	int j;
	t_list *tmp;

	i = shell->col;
	j = 0;
	tmp = shell->hist;
	while (tmp)
	{
		if (j == i)
			return(tmp->content);
		tmp = tmp->next;
		j++;
	}
	return (NULL);
}
void ft_arrow_up(t_shell *shell)
{
	if (shell->col != 0)
	{
		shell->col--;
		tputs(restore_cursor, 1, putchar_term);
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		shell->line = line_hist(shell);
	}
}

void	ft_arrow_down(t_shell *shell)
{
	if (shell->col < shell->new_col)
	{
		shell->col++;
		tputs(restore_cursor, 1, putchar_term);
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		shell->line = line_hist(shell);
	}
}

void	add_to_history(t_shell *shell)
{
	t_list *tmp;

	tmp = shell->hist;
	if (strcmp(shell->line, ""))
	{
		if(shell->hist == NULL)
			shell->hist = ft_lstnew(ft_strdup(shell->line));
		else
		{
			ft_lstadd_back(&shell->hist, ft_lstnew(ft_strdup(shell->line)));
		}
	}

}
void	ft_arrow_enter(t_shell *shell, int i)
{
	shell->line[i] = '\0';
	shell->col++;
	shell->new_col = shell->col;
	add_to_history(shell);
	ft_putstr("\n");
	ft_prompt();
	tputs(save_cursor, 1, putchar_term);
}

void	delete_end(t_shell *shell, int *col, int *row, char *cm, char *ce)
{
	if (*col != 0 && *col > 11)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_term);
	tputs(ce, 1, putchar_term);
	shell->line = ft_substr(shell->line, 0, ft_strlen(shell->line) - 1);
}
void	read_line(t_shell *shell)
{
	int	c;
	int	i;

	i = 0;
	char *cm = tgetstr("cm", NULL); //cursor motion
	char *ce = tgetstr("ce", NULL); //clear line from cursor
	int row;
	int col;
	while (read(0, &c, sizeof(c)) >= 0)
	{
		get_cursor_position(&col, &row);
		if (c == CTRLD && i == 0)
			ft_ctrld(shell);
		if (c == UP_ARROW)
			ft_arrow_up(shell);
		else if (c == DOWN_ARROW)
			ft_arrow_down(shell);
		else if (c == ENTER_ARROW)
		{
			ft_arrow_enter(shell, i);
			i = 0;
		}
		else if (c == BACKSPACE)
			delete_end(shell, &col, &row, cm, ce);
		else
		{
			shell->line[i++] = c;
			write(1, &c, 1);
		}
		c = 0;
	}
}

void	ft_minishell(t_shell *shell)
{
	struct termios	term;
	char			*term_name;
	int				c;
	int				i;

	term_name = getenv("TERM");
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(0, term_name);
	read_line(shell);
}

void	ft_initialise(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->cmd = NULL;
	shell->hist = NULL;
	shell->line = (char *)malloc(sizeof(char));
	shell->col = 0;
	shell->new_col = 0;
	shell->fork = 0;
}

int 	main(int ac, char **av, char **envp)
{
	t_shell		shell;

	ft_initialise(&shell, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_prompt();
	ft_minishell(&shell);
	return (0);

}
