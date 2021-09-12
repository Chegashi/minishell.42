/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:47:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 18:47:30 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_mem(void)
{
	t_mem	*tmp;

	tmp = g_data.mem;
	while (tmp)
	{
		free(tmp->line);
		tmp->line = NULL;
		tmp = tmp->next;
	}
}

int	count_tabl(char **tabl)
{
	int	count;

	count = 0;
	while (tabl[count])
		count++;
	return (count);
}

void	free_ta(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
	tabl = NULL;
}

void	free_pipes(t_pipes *pipes)
{
	t_pipes	*tmp;

	if (pipes == NULL)
		return ;
	while (pipes)
	{
		if (pipes->line)
			ft_free(pipes->line);
		if (pipes->params && count_tabl(pipes->params) > 0)
			free_ta(pipes->params);
		tmp = pipes;
		pipes = pipes->next;
		free(tmp);
	}
	pipes = NULL;
}

void	free_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd == NULL)
		return ;
	while (cmd)
	{
		if (cmd->line)
			ft_free(cmd->line);
		if (cmd->pipes)
			free_pipes(cmd->pipes);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	cmd = NULL;
}
