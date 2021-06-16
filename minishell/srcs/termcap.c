/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:27:37 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 17:02:45 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_char(t_shell *shell, int c, int *col)
{
	char	*str;
	char	*tmp;

	shell->enter = 0;
	if (c != '\n' && ft_isprint(c))
	{
		write(0, &c, 1);
		if (*col == tgetnum("co"))
		{	
			write(1, tgetstr("do", NULL), ft_strlen(tgetstr("do", NULL)));
			*col = 1;
		}
		else
			(*col)++;
		str = malloc(sizeof(char) * 2);
		str[0] = (char)c;
		str[1] = '\0';
		tmp = shell->line;
		shell->line = ft_strjoin(shell->line, str);
		free(tmp);
		free(str);
	}
}

void	ft_arrow_up(t_shell *shell, int c, int *col)
{
	char	*tmp;

	if (!shell->enter)
	{
		shell->enter = 1;
		tmp = ft_histlast(shell->hist)->line;
		ft_histlast(shell->hist)->line = ft_strdup(shell->line);
		free(tmp);
	}
	if (shell->hist_last && shell->hist_last->prev)
	{
		write(1, "\r", 1);
		ft_prompt();
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		shell->hist_last = shell->hist_last->prev;
		tmp = shell->line;
		shell->line = ft_strdup(shell->hist_last->line);
		free(tmp);
		ft_putstr(shell->line);
	}
	if (shell->line)
		*col = ft_strlen(shell->line) + 11;
	else
		*col = 11;
}

void	ft_arrow_down(t_shell *shell, int c, int *col)
{
	char	*tmp;

	if (shell->hist_last && shell->hist_last->next)
	{
		write(1, "\r", 1);
		ft_prompt();
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		shell->hist_last = shell->hist_last->next;
		tmp = shell->line;
		shell->line = ft_strdup(shell->hist_last->line);
		free(tmp);
		ft_putstr(shell->line);
	}
	if (shell->line)
		*col = ft_strlen(shell->line) + 11;
	else
		*col = 11;
}

void	read_line(t_shell *shell)
{
	int	col;
	int	row;

	shell->c = 0;
	col = 0;
	while (read(0, &shell->c, sizeof(shell->c)) > 0)
	{
		get_cursor_position(shell, &col, &row);
		if (shell->c == UP_ARROW)
			ft_arrow_up(shell, shell->c, &col);
		else if (shell->c == DOWN_ARROW)
			ft_arrow_down(shell, shell->c, &col);
		else if (shell->c == BACKSPACE)
			delete_end(shell, &col, &row);
		else if (shell->c == CTRLD)
			ft_ctrld(shell);
		else if (shell->c == ENTER_ARROW)
		{
			ft_enter_line(shell);
			break ;
		}
		else
			join_char(shell, shell->c, &col);
		shell->c = 0;
	}
}

void	ft_minishell_help(t_shell *shell)
{
	struct termios	term;
	char			*term_name;

	term_name = getenv("TERM");
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &shell->orig_term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(0, term_name);
	shell->line = ft_strdup("");
	shell->hist_last = ft_histlast(shell->hist);
	shell->enter = 0;
	if (!ft_histsize(shell->hist))
		shell->hist = ft_histnew(ft_strdup(""));
	read_line(shell);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->orig_term);
}
