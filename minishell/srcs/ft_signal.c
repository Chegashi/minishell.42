/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:19:27 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		ft_prompt();
	}
	else if (signum == SIGQUIT)
	{
		if (g_data.fork > 0)
			ft_putstr("Quit: 3\n");
	}
}
