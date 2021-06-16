/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:30:27 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:01:53 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd_list(t_cmd **cmd, char *line)
{
	if ((*cmd))
		add_cmd_list(&((*cmd)->next), line);
	else if ((*line))
	{
		(*cmd) = (t_cmd *)malloc(sizeof(t_cmd));
		(*cmd)->line = line;
		(*cmd)->pipes = NULL;
		(*cmd)->next = NULL;
	}
}

void	stock_line(t_cmd **cmd, char *line)
{
	char	**cmd_arr;
	char	*tmp;
	int		i;

	i = 0;
	cmd_arr = cmd_split(line, ';');
	while (cmd_arr[i])
	{
		add_cmd_list(cmd, cmd_arr[i]);
		i++;
	}
	if (cmd_arr)
	{
		free(cmd_arr);
		cmd_arr = NULL;
	}
}

int 	stock_command(t_cmd **cmd, char *line)
{
	stock_line(cmd, line);
	if (fill_pipes(*cmd) == -1)
		return (-1);
	return (0);
}
