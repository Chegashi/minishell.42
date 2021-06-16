/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:30:30 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	count_redir(char **params)
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

int 	check_not_qt(char **str, int pos)
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

int 	size_params(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	remove_params(t_pipes *pipes, int pos)
{
	int	size;

	size = size_params(pipes->params);
	while (pos < size)
	{
		pipes->params[pos] = pipes->params[pos + 1];
		pos++;
	}
	pipes->params[pos + 1] = NULL;
	size--;
}
