/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:14:03 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 18:14:28 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msg_error(char *line, char c, int i)
{	
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	g_data.n_exit = 258;
	if (line[i + 1] == c || (i > 0 && line[i - 1] == c))
	{
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
	}
	else
		ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	end_pipe_file(char *line, int i)
{
	while (line[--i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '|'))
	{
		if (line[i] == '|')
		{
			ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
			g_data.n_exit = 258;
			return (-1);
		}
	}
	return (0);
}

int	end_semi_file(char *line, int i)
{
	while (line[--i] && (line[i] == ' '
			|| line[i] == '\t' || line[i] == ';' || line[i] == '|'))
	{
		if (line[i] == '|')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 2);
			g_data.n_exit = 258;
			return (-1);
		}
	}
	return (0);
}

int	ft_quote(char *line, int i)
{
	char	quote;

	while (line[i] && (line[i] == '\'' || line[i] == '"'))
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (i == ((int)ft_strlen(line)))
			break ;
		else
			i++;
	}
	return (i);
}
