/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:39 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:43:48 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command(char *s)
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
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_data.n_exit = 127;
}

void	error_no_file(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_data.n_exit = 127;
}

void	error_is_dir(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": is a directory", 2);
	g_data.n_exit = 127;
}

int	check_error_cmd(t_pipes *pipe)
{
	if (pipe->params[0][0] == '/')
	{
		if (check_directory(pipe->params[0]) == 0)
			return (-1);
	}
	else if (check_command(pipe->params[0]) == 0
		&& search_path(pipe->params[0], pipe, NULL) == 0
		&& found_redirection(pipe->params[0]) == 0)
	{
		ft_not_found(pipe->params[0]);
		return (-1);
	}
	return (0);
}
