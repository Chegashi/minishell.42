/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:38:43 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 14:25:33 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_data.ctrl_c = 1;
		g_data.stdin_cpy = dup(0);
		close(0);
	}
	else if (sig == SIGQUIT)
	{
		if (g_data.fork > 0)
		{
			g_data.fork = 0;
			printf("Quit: 3\n");
		}
	}
}

void	ctrl_d(void)
{
	ft_putstr_fd("\rminishell$ exit \n", 2);
	g_data.done = 1;
}

void	ft_parse(void)
{
	char	*status;

	add_history(g_data.line);
	if (*g_data.line && is_error(g_data.line, '|', -1) != -1
		&& is_error(g_data.line, ';', -1) != -1
		&& not_comp_quote(g_data.line) != -1
		&& is_redir_error(g_data.line) != -1)
	{
		stock_command(&g_data.cmd, g_data.line);
		ft_excute();
	}
}

void	ft_minishell(void)
{
	while (!g_data.done)
	{
		g_data.line = readline("minishell$ ");
		if (g_data.ctrl_c == 1)
		{
			g_data.ctrl_c = 0;
			dup2(g_data.stdin_cpy, 0);
			close(g_data.stdin_cpy);
			continue ;
		}
		else if (!g_data.line)
			ctrl_d();
		else if (*g_data.line)
			ft_parse();
		free(g_data.line);
		clear_mem();
		clear_data();
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_data.done = 0;
	g_data.ctrl_c = 0;
	g_data.fork = 0;
	init_envp(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_minishell();
	return (0);
}
