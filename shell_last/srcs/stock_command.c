/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:35:06 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 17:59:43 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**change_params(char *line)
{
	char	**params;
	int		i;

	i = 0;
	params = splite_space(line);
	if (params[i] && ft_strcmp(params[i], "export"))
	{
		while (params[i])
		{
			add_to_mem(&g_data.mem, params[i]);
			params[i] = remove_quote(params[i], 0, 0);
			i++;
		}
	}
	return (params);
}

void	add_pipe_list(t_pipes **pipe, char *line)
{
	if ((*pipe))
		add_pipe_list(&((*pipe)->next), line);
	else if ((*line))
	{
		(*pipe) = (t_pipes *)malloc(sizeof(t_pipes));
		(*pipe)->line = split_redirection(line);
		(*pipe)->params = change_params((*pipe)->line);
		ft_redirection(*pipe);
		(*pipe)->next = NULL;
	}
}

void	stock_pipes(t_cmd **cmd)
{
	char	**pipe_arr;
	int		i;

	i = 0;
	pipe_arr = cmd_split((*cmd)->line, '|');
	while (pipe_arr[i])
	{
		add_pipe_list(&(*cmd)->pipes, pipe_arr[i]);
		i++;
	}
	if (pipe_arr)
	{
		free(pipe_arr);
		pipe_arr = NULL;
	}
}

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

int	stock_command(t_cmd **cmd, char *line)
{
	char	**cmd_arr;
	int		i;

	i = 0;
	cmd_arr = cmd_split(line, ';');
	while (cmd_arr[i])
	{
		add_cmd_list(cmd, cmd_arr[i]);
		i++;
	}
	free(cmd_arr);
	cmd_arr = NULL;
	return (0);
}
