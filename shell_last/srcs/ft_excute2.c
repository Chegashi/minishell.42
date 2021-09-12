/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:11:42 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 19:11:43 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_start(int i, t_pipes *cmd, int p[g_data.n_pi][2])
{
	int	j;

	if (i > 0)
		dup2(p[i - 1][0], STDIN_FILENO);
	else if (cmd->inp)
	{
		dup2(cmd->inp, STDIN_FILENO);
		close(cmd->inp);
	}
	if (i < g_data.n_cmd - 1)
		dup2(p[i][1], STDOUT_FILENO);
	else if (cmd->out)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	j = 0;
	while (j < g_data.n_pi)
	{
		close(p[j][0]);
		close(p[j][1]);
		j++;
	}
	call_command(cmd, cmd->params[0]);
	exit(EXIT_SUCCESS);
}

void	pipe_end(int i, t_pipes *cmd, int p[g_data.n_pi][2])
{
	int	j;

	g_data.pids[i] = g_data.pid;
	if (i == g_data.n_cmd - 1)
	{
		j = 0;
		while (j < g_data.n_pi)
		{
			close(p[j][0]);
			close(p[j][1]);
			j++;
		}
		j = 0;
		while (j < g_data.n_cmd)
		{
			waitpid(g_data.pids[j], &(g_data.status[j]), 0);
			if (WIFEXITED(g_data.status[j]))
				g_data.n_exit = WEXITSTATUS(g_data.status[j]);
			j++;
		}
	}
}

void	ft_pipe(t_pipes *cmd, int i, int p[g_data.n_pi][2])
{
	int	j;

	j = 0;
	g_data.pid = fork();
	g_data.fork++;
	if (g_data.pid < 0)
	{
		ft_putendl_fd(strerror(errno), 1);
		exit(0);
	}
	else if (g_data.pid == 0)
		pipe_start(i, cmd, p);
	else
		pipe_end(i, cmd, p);
}
