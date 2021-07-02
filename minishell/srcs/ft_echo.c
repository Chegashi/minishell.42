/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:45 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/02 16:16:50 by mochegri         ###   ########.fr       */
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

void	ft_echo(t_v_env *venv, t_pipes *pipe)
{

	int		new_line;
	int		i;

	new_line = 1;
	while (pipe->params[i])
	{
		if (!ft_strcmp(pipe->params[i], "-n") && new_line)
				{	printf("0|\n");
			new_line = 0;}
		else if (pipe->params[i][0] == '$')
		{		printf("-1|\n");
			ft_putstr(get_value(pipe->params[i] + 1, venv));}
		else
		{	printf("1|\n");
			ft_putstr(pipe->params[i]);
		}
		ft_putstr(" ");
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}