/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:04 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/01 09:18:31 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

int 	ft_prompt(void)
{
	ft_putstr("🍑\e[1;32mminishell🍑$ \e[0;37m");
	return (1);
}
