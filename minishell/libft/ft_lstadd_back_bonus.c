/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:38:59 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/20 00:59:40 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*head;

	head = *alst;
	if (*alst)
	{
		while (head->next)
		{
			head = head->next;
		}
		head->next = new;
	}
	else
		*(alst) = new;
}
