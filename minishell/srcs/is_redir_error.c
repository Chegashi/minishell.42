/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:24:26 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:00:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_exterieur(int count)
{
	ft_putstr("minishell: ");
	ft_putstr("syntax error near unexpected token `");
	if (count >= 4)
		ft_putstr(">>'\n");
	else
		ft_putstr(">'\n");
	return (-1);
}

int	parse_inferieur(int count)
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

int	found_redirection(char *line)
{
	if (ft_strcmp(line, ">") == 0
		|| ft_strcmp(line, ">>") == 0 || ft_strcmp(line, "<") == 0)
		return (1);
	else
		return (0);
}

int	check_parse_redir(char *line, int start, int end)
{
	int	i;
	int	count;
	char *tmp;
	count = 0;
	i = 0;
	if (end > 0)
		line = ft_substr(line, start, end);
	if (!found_redirection(line))
	{
		while (line[i])
		{
			i = check_redir(line, i, &count);
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
	free(line);
	return (0);
}

int	is_redir_error(char *line)
{
	int	i;
	int	q;
	int	end;
	int	start;

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
