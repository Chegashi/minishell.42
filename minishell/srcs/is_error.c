/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:41:02 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	msg_error(char *line, char c, int i)
{	
	ft_putstr("Minishell: syntax error near unexpected token `");
	if (line[i + 1] == c || (i > 0 && line[i - 1] == c))
	{
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
	}
	else
		ft_putchar_fd(c, 2);
	ft_putstr("'\n");
	return (-1);
}

int	end_pipe_file(char *line, int i)
{
	while (line[--i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '|'))
	{
		if (line[i] == '|')
		{
			ft_putstr("Minishell: syntax error: unexpected end of file\n");
			return (-1);
		}
	}
	return (0);
}

int	is_error_help(char *line, int i, char c)
{
	while (line[++i] && (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '>' || line[i] == '<' || line[i] == c))
	{
		if (line[i] == c)
			return (msg_error(line, c, i));
	}
	return (i);
}

int	is_error(char *line, char c)
{
	int	i;

	i = -1;
	if (line[0] == c)
		return (msg_error(line, c, 0));
	i = is_error_help(line, i, c);
	while (line[i])
	{
		i = ft_quote(line, i);
		if (i == (int)ft_strlen(line))
			break ;
		if (line[i] && line[i] == c)
		{
			i = is_error_help(line, i, c);
			if (line[i] == '\0')
			{
				if (c == '|' && end_pipe_file(line, i) == -1)
					return (-1);
				break ;
			}
		}
		i++;
	}
	return (0);
}
