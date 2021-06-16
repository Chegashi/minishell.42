/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:54:38 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:24:57 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_table(char **tabl, int j)
{
	while (j--)
		free(tabl[j]);
	free(tabl);
	tabl = NULL;
	return (NULL);
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
		if (pipes->is_red)
		{
			if (pipes->params && count_tabl(pipes->params) > 0)
				free_ta(pipes->params);
			if (pipes->file && count_tabl(pipes->file) > 0)
				free_ta(pipes->file);
			if (pipes->type && count_tabl(pipes->type) > 0)
				free_ta(pipes->type);
		}
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

void	clear_data(t_shell *shell)
{
	if (shell->cmd)
	{
		free_list(shell->cmd);
		shell->cmd = NULL;
	}
}
