/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:27:26 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 17:55:19 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	putchar_term(int c)
{
	return (write(1, &c, 1));
}

int 	nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	delete_end(t_shell *shell, int *col, int *row)
{
	char	*cm;
	char	*ce;
	char	*tmp;

	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	shell->enter = 0;
	if (*(shell->line) != 0)
	{
		if (*col > 0 && *col > 11)
			(*col)--;
		write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
		write(1, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
		tmp = shell->line;
		shell->line = ft_substr(shell->line, 0, ft_strlen(shell->line) - 1);
		free(tmp);
	}
}

void	get_curs_pos_help(t_shell *shell, int *col, int *rows, int a)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (shell->buf[i])
	{
		if (shell->buf[i] >= '0' && shell->buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&shell->buf[i]) - 1;
			else
			{
				temp = atoi(&shell->buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}	
}

void	get_cursor_position(t_shell *shell, int *col, int *rows)
{
	int	a;
	int	i;
	int	ret;
	int	temp;

	a = 0;
	i = 0;
	write(0, "\033[6n", 4);
	ret = read(0, shell->buf, 254);
	shell->buf[ret] = '\0';
	get_curs_pos_help(shell, col, rows, a);
}
