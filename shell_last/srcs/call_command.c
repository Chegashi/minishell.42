/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:17:57 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/02 16:10:42 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_command(t_pipes *pipe, char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		ft_echo(pipe);
	else if (ft_strcmp(s, "cd") == 0)
		ft_cd(pipe->params);
	else if (ft_strcmp(s, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(s, "export") == 0)
		ft_export(pipe, 1);
	else if (ft_strcmp(s, "unset") == 0)
		ft_unset(pipe->params);
	else if (ft_strcmp(s, "env") == 0)
		ft_env();
	else if (ft_strcmp(s, "exit") == 0)
		ft_exit(pipe);
	else
		execve(pipe->params[0], pipe->params, g_data.envp);
}

void	ft_builtins2(t_pipes *pipe)
{
	if (ft_strcmp(pipe->params[0], "echo") == 0)
		ft_echo(pipe);
	else if (ft_strcmp(pipe->params[0], "cd") == 0)
		ft_cd(pipe->params);
	else if (ft_strcmp(pipe->params[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(pipe->params[0], "export") == 0)
		ft_export(pipe, 1);
	else if (ft_strcmp(pipe->params[0], "unset") == 0)
		ft_unset(pipe->params);
	else if (ft_strcmp(pipe->params[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(pipe->params[0], "exit") == 0)
		ft_exit(pipe);
}

int	ft_builtins(t_pipes *pipe)
{
	int	std_out;
	int	std_in;

	std_out = dup(1);
	std_in = dup(0);
	if (pipe->out != 0)
	{
		dup2(pipe->out, 1);
		close(pipe->out);
	}
	if (pipe->inp != 0)
	{
		dup2(pipe->inp, 0);
		close(pipe->inp);
	}
	ft_builtins2(pipe);
	dup2(std_out, 1);
	dup2(std_in, 0);
	close(std_out);
	close(std_in);
	return (1);
}
