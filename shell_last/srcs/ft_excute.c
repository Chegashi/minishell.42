/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:27:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:57:27 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipe2(void)
{
	if (g_data.status)
		free(g_data.status);
	if (g_data.pids)
		free(g_data.pids);
}

void	execute_pipe(t_pipes *pipe_l)
{
	int		i;
	t_pipes	*cmd;
	int		pipes[MAX_PATH][2];

	i = 0;
	g_data.status = (int *)malloc(sizeof(int) * g_data.n_cmd);
	g_data.pids = (int *)malloc(sizeof(int) * g_data.n_cmd);
	cmd = pipe_l;
	while (i < g_data.n_pi)
	{
		if (pipe(pipes[i]) < 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < g_data.n_cmd && cmd)
	{
		if (cmd->params[0] && check_error_cmd(cmd) != -1)
			ft_pipe(cmd, i, pipes);
		i++;
		cmd = cmd->next;
	}
	execute_pipe2();
}

int	size_without_sp(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

void	ft_excute2(t_cmd *cmd, int count)
{
	g_data.n_cmd = count_pipes(cmd->pipes);
	g_data.n_pi = g_data.n_cmd - 1;
	if (g_data.n_pi == 0 && cmd->pipes->params[0]
		&& ft_strcmp(cmd->pipes->params[0], "exit") == 0)
		ft_exit(cmd->pipes);
	else if (g_data.n_pi == 0 && cmd->pipes->params[0]
		&& check_command(cmd->pipes->params[0]) == 1
		&& ft_builtins(cmd->pipes) == 1)
		count = 0;
	else
		execute_pipe(cmd->pipes);
}

void	ft_excute(void)
{
	t_cmd	*cmd;
	int		count;
	char	*status;

	cmd = g_data.cmd;
	while (cmd)
	{
		status = ft_itoa(g_data.n_exit);
		add_to_mem(&g_data.mem, cmd->line);
		cmd->line = str_replace(cmd->line, "$?", status, 2);
		cmd->line = replace_variable(cmd->line);
		add_to_mem(&g_data.mem, status);
		if (size_without_sp(cmd->line) > 0)
		{
			g_data.error = 0;
			stock_pipes(&cmd);
			if (!g_data.error)
				ft_excute2(cmd, count);
		}
		cmd = cmd->next;
	}
}
