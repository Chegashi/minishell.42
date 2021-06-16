/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:27:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:29:44 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_start(t_shell *shell, int i, t_pipes *cmd)
{
	int	j;

	if (i > 0)
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (i < shell->n_cmd - 1)
		dup2(shell->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < shell->n_pi)
	{
		close(shell->pipes[j][0]);
		close(shell->pipes[j][1]);
		j++;
	}
	if (cmd->out != 0)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	if (cmd->inp != 0)
	{
		dup2(cmd->inp, 0);
		close(cmd->inp);
	}
	execvp(cmd->params[0], cmd->params);
}

void	pipe_end(t_shell *shell, int i, t_pipes *cmd)
{
	int	j;

	shell->pids[i] = shell->pid;
	if (i == shell->n_cmd - 1)
	{
		j = 0;
		while (j < shell->n_pi)
		{
			close(shell->pipes[j][0]);
			close(shell->pipes[j][1]);
			j++;
		}
		j = 0;
		while (j < shell->n_cmd)
		{
			waitpid(shell->pids[j], &(shell->status[j]), 0);
			j++;
		}
	}
}

void	ft_pipe(t_shell *shell, t_pipes *cmd, int i)
{
	int	j;

	j = 0;
	shell->pid = fork();
	g_data.fork++;
	if (shell->pid < 0)
	{
		perror("Fork");
		exit(0);
	}
	else if (shell->pid == 0)
		pipe_start(shell, i, cmd);
	else
		pipe_end(shell, i, cmd);
}

void	execute_pipe(t_shell *shell, t_pipes *pipe_l)
{
	int		i;
	t_pipes	*cmd;

	i = 0;
	shell->pipes[0] = (int *)malloc(sizeof(int) * shell->n_pi);
	shell->pipes[1] = (int *)malloc(sizeof(int) * shell->n_pi);
	shell->status = (int *)malloc(sizeof(int) * shell->n_cmd);
	shell->pids = (int *)malloc(sizeof(int) * shell->n_cmd);
	cmd = pipe_l;
	while (i < shell->n_pi)
	{
		pipe(shell->pipes[i]);
		i++;
	}
	i = 0;
	while (i < shell->n_cmd && cmd)
	{
		if (check_error_cmd(cmd) == -1)
			break ;
		ft_pipe(shell, cmd, i);
		i++;
		cmd = cmd->next;
	}
}

void	ft_excute(t_shell *shell)
{
	t_cmd	*cmd;
	int		count;

	cmd = shell->cmd;
	while (cmd)
	{
		shell->n_cmd = count_pipes(cmd->pipes);
		shell->n_pi = shell->n_cmd - 1;
		execute_pipe(shell, cmd->pipes);
		cmd = cmd->next;
	}
}
