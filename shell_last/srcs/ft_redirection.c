/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:56:43 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 17:57:17 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redi_errors(char *line, int start, int nb_red)
{
	char	*tmp;

	if (nb_red > 0)
	{
		tmp = ft_substr(line, start, nb_red);
		if (!found_redirection(tmp))
		{
			error_count_redirection(tmp);
			add_to_mem(&g_data.mem, tmp);
			return (-1);
		}
		else
			add_to_mem(&g_data.mem, tmp);
	}
	return (0);
}

int	is_redir_error(char *line)
{
	int	i;
	int	q;
	int	start;
	int	nb_red;

	q = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !q)
			q = 0;
		else if ((line[i] == '\'' || line[i] == '\"') && q)
			q = 1;
		nb_red = 0;
		start = i;
		while (line[i] && (line[i] == '>' || line[i] == '<'))
		{
			nb_red++;
			i++;
		}
		if (start != i && check_redi_errors(line, start, nb_red) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	count_redir(char **params)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (params[i])
	{
		if (found_redirection(params[i]))
			count++;
		i++;
	}
	return (count);
}

int	check_not_qt(char **str, int pos)
{
	int	i;
	int	q;
	int	j;

	i = 0;
	q = 0;
	while (i < pos)
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '\"' || str[i][j] == '\"') && !q)
				q = 1;
			else if ((str[i][j] == '\"' || str[i][j] == '\"') && q)
				q = 0;
			j++;
		}
		i++;
	}
	return (q);
}
