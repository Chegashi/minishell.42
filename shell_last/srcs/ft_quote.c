/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:13:34 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 18:13:36 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	is_error_i(char *line, char c)
{
	int	i;

	i = -1;
	if (line[0] == c)
		return (msg_error(line, c, 0));
	i = is_error_help(line, i, c);
	return (i);
}

int	is_error(char *line, char c, int i)
{
	i = is_error_i(line, c);
	if (i == -1)
		return (-1);
	while (line[i])
	{
		i = ft_quote(line, i);
		if (i == (int)ft_strlen(line))
			break ;
		if (line[i] && line[i] == c)
		{
			i = is_error_help(line, i, c);
			if (i == -1)
				return (-1);
			if (line[i] == '\0')
			{
				if (c == '|' && end_pipe_file(line, i) == -1)
					return (-1);
				if (c == ';' && end_semi_file(line, i) == -1)
					return (-1);
				break ;
			}
		}
		i++;
	}
	return (0);
}

int	quote_error(void)
{
	ft_putstr_fd("bash: syntax error: unexpected end of file \n", 2);
	g_data.n_exit = 258;
	return (-1);
}

int	not_comp_quote(char *line)
{
	int	i;
	int	sngl;
	int	dbl;

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
		return (quote_error());
	return (0);
}
