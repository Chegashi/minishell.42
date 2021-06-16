/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:33:16 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:25:07 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pipe_list(t_pipes **pipe, char *line)
{
	char	*tmp;

	if ((*pipe))
		add_pipe_list(&((*pipe)->next), line);
	else if ((*line))
	{
		(*pipe) = (t_pipes *)malloc(sizeof(t_pipes));
		(*pipe)->line = split_redirection(line);
		(*pipe)->params = splite_space((*pipe)->line);
		(*pipe)->is_red = 0;
		ft_redirection(*pipe);
		(*pipe)->next = NULL;
	}
}

int 	fill_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	**pipe_cmd;
	int		i;
	char	*str;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		pipe_cmd = cmd_split(tmp->line, '|');
		while (pipe_cmd[i])
		{
			add_pipe_list(&tmp->pipes, pipe_cmd[i]);
			i++;
		}
		// if (ft_pipes_redir(tmp->pipes) == -1)
		// 	return (-1);
		free(pipe_cmd);
		tmp = tmp->next;
	}
	return (0);
}
