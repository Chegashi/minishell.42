/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:54:58 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 17:00:44 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char const *s, int i)
{
	while (s[i] && check_space(s[i]))
		i++;
	return (i);
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

int	count_tabl(char **tabl)
{
	int	count;

	count = 0;
	while (tabl[count])
		count++;
	return (count);
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
