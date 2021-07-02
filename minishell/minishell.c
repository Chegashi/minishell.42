/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:38:43 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/02 12:38:28 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse(t_shell *shell)
{
	if (shell->line[0] && is_error(shell->line, '|') != -1
		&& is_error(shell->line, ';') != -1
		&& not_comp_quote(shell->line) != -1
		&& is_redir_error(shell->line) != -1)
	{
		if (stock_command(&shell->cmd, shell->line) != -1)
		{
			ft_excute(shell);
		}
	}
}

void	ft_initialise(t_shell *shell, char **envp)
{
	shell->envp = init_envp(envp);
	shell->cmd = NULL;
	shell->fork = 0;
	shell->hist_last = NULL;
	shell->hist = NULL;
	shell->enter = 0;
}

void	ft_minishell(t_shell *shell)
{
	while (1)
	{
		ft_minishell_help(shell);
		ft_parse(shell);
		ft_prompt();
		ft_free(shell->line);
		clear_data(shell);
		g_data.fork = 0;
	}
}

void	clear_all_data(t_shell *shell)
{
	shell->envp = NULL;
	free(shell->cmd);
	free_hist(shell->hist);
	free_hist(shell->hist_last);
	ft_free(shell->line);
}

int 	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	g_data.fork = 0;
	ft_initialise(&shell, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_prompt();
	ft_minishell(&shell);
	clear_all_data(&shell);
	return (0);
}
