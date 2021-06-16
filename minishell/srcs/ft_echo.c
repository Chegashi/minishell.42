/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:45 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_without_qt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] == '\\')
			i++;
		if ((str[i] != '\"' && str[i] != '\''))
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

int 	check_echoline(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	ft_echo(t_shell *shell, t_pipes *pipe)
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
		echo_without_qt(pipe->params[i]);
		if (pipe->params[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (l == 0)
		ft_putchar_fd('\n', 1);
}
