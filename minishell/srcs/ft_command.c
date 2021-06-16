/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:39 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/10 20:36:25 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	check_command(char *s)
{
	if (ft_strcmp(s, "echo") == 0 || ft_strcmp(s, "cd") == 0
		|| ft_strcmp(s, "pwd") == 0 || ft_strcmp(s, "export") == 0
		|| ft_strcmp(s, "unset") == 0 || ft_strcmp(s, "env") == 0
		|| ft_strcmp(s, "exit") == 0)
		return (1);
	return (0);
}

void	ft_not_found(char *cmd)
{
	ft_putstr("minishell: ");
	ft_putstr(cmd);
	ft_putstr(": command not found\n");
}

int 	check_error_cmd(t_pipes *pipe)
{
	if (check_command(pipe->params[0]) == 0
		&& search_path(pipe->params[0], pipe) == 0
		&& found_redirection(pipe->params[0]) == 0
		&& pipe->params[0][0] != '/')
	{
		ft_not_found(pipe->params[0]);
		return (-1);
	}
	return (0);
}
