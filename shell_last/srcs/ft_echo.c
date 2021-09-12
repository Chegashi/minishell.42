/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:24:28 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 19:24:29 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echoline(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	ft_echo(t_pipes *pipe)
{
	int	i;
	int	l;

	l = 0;
	i = 1;
	while (pipe->params[i] && pipe->params[i][0] == '-'
		&& check_echoline(pipe->params[i]))
	{
		l++;
		i++;
	}
	while (pipe->params[i])
	{
		ft_putstr(pipe->params[i]);
		if (pipe->params[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (l == 0)
		ft_putchar_fd('\n', 1);
}
