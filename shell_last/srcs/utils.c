/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:33:56 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 17:33:58 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

void	ft_putstr(char *line)
{
	ft_putstr_fd(line, 1);
}

int	count_pipes(t_pipes *pipes)
{
	t_pipes	*tmp;
	int		count;

	count = 0;
	tmp = pipes;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	add_to_mem(t_mem **mem, char *line)
{
	if ((*mem))
		add_to_mem(&((*mem)->next), line);
	else if ((*line))
	{
		(*mem) = (t_mem *)malloc(sizeof(t_mem));
		(*mem)->line = line;
		(*mem)->next = NULL;
	}
}
