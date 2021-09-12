/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:12:37 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 18:12:40 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_redirection(char *line)
{
	if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, "<<") == 0
		|| ft_strcmp(line, ">>") == 0 || ft_strcmp(line, "<") == 0)
		return (1);
	else
		return (0);
}

int	parse_exterieur(int count)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (count >= 4)
		ft_putstr_fd(">>'\n", 2);
	else
		ft_putstr_fd(">'\n", 2);
	g_data.n_exit = 258;
	return (-1);
}

int	parse_inferieur(int count)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (count > 5)
		ft_putstr_fd("<<<'\n", 2);
	else if (count > 4)
		ft_putstr_fd("<<'\n", 2);
	else
		ft_putstr_fd("<'\n", 2);
	g_data.n_exit = 258;
	return (-1);
}

int	check_redir(char *line, int i, int *count)
{
	while (line[i] && line[i] == '>')
	{
		(*count)++;
		i++;
	}
	return (i);
}

int	error_count_redirection(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
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
		i++;
	}
	return (0);
}
