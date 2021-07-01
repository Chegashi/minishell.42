/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 21:17:21 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/01 21:26:41 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	echo(char *str, t_v_env *head)
{
	char	**worlds;
	int		new_line;

	worlds =ft_split(str, ' ');
	new_line = 1;
	while(*worlds)
	{
		if (!ft_strcmp(*worlds, "-n") && new_line)
			new_line = 0;
		if (**worlds == '$')
			ft_putstr(get_value(str + 1, head));
		else
			ft_putstr(str);
		str++;
	}
	if (new_line)
	write(1, "\n", 1);
}