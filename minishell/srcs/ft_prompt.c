/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:20:04 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 17:04:50 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

int 	ft_prompt(void)
{
	ft_putstr("\e[1;32mminishell$ \e[0;37m");
	return (1);
}
