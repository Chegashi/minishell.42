	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   echo.c                                             :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2021/07/01 21:17:21 by mochegri          #+#    #+#             */
	/*   Updated: 2021/07/02 08:46:43 by mochegri         ###   ########.fr       */
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
			else if (**worlds == '$')
				ft_putstr(get_value(key_from_str(str + 1), head));
			else
				ft_putstr(*worlds);
			ft_putstr(" ");
			worlds++;
			//printf("%s\n", *worlds++);
		}
		if (new_line)
		write(1, "\n", 1);
	}
