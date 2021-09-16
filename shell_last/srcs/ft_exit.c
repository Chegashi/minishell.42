/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:05:09 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:07:40 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg_error_exit(char *msg, char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	write(2, str, ft_strlen(str));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 2);
}

int	str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit2(t_pipes *pipe)
{
	if (pipe->params[1] && ft_isdigit(pipe->params[1][0]) && pipe->params[2])
		g_data.done = 0;
	else
		exit(g_data.n_exit);
}

void	ft_exit(t_pipes *pipe)
{
	if (g_data.n_pi == 0)
	{
		ft_putstr("exit\n");
		g_data.done = 1;
		g_data.n_exit = 0;
	}
	if (pipe->params && pipe->params[1])
	{
		if ((!ft_isdigit(pipe->params[1][0]) && pipe->params[1][0] != '-'
			&& pipe->params[1][0] != '+') || !str_digit(pipe->params[1]))
		{
			msg_error_exit(": numeric argument required", pipe->params[1]);
			g_data.n_exit = 255;
		}
		else
		{
			g_data.n_exit = ft_atoi(pipe->params[1]);
			if (pipe->params[2])
			{
				msg_error_exit("too many arguments", "");
				g_data.n_exit = 1;
			}
		}
	}
	ft_exit2(pipe);
}
