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

void	call_command(t_shell *shell, t_pipes *pipe, char *s)
{
	if (ft_strcmp(s, "echo") == 0 || ft_strcmp(s, "ECHO") == 0)
		ft_echo(shell->envp, pipe);
	else if (ft_strcmp(s, "cd") == 0 || ft_strcmp(s, "CD") == 0)
		ft_cd(shell, pipe);
	else if (ft_strcmp(s, "pwd") == 0 || ft_strcmp(s, "PWD") == 0)
		ft_pwd(pipe);
	else if (ft_strcmp(s, "export") == 0)
		ft_export(shell, pipe);
	else if (ft_strcmp(s, "unset") == 0)
		ft_unset(shell, pipe);
	else if (ft_strcmp(s, "env") == 0 || ft_strcmp(s, "ENV") == 0)
		ft_env(shell->envp);
	else if (ft_strcmp(s, "exit") == 0)
		ft_exit(shell, pipe);
	else
		execve(pipe->params[0], pipe->params, NULL);
}
