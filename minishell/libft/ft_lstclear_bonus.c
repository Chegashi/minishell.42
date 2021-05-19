/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:17:59 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/22 22:14:51 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *next_ls;
	t_list *head;

	head = *lst;
	if (head)
	{
		while (head)
		{
			next_ls = head->next;
			ft_lstdelone(head, (*del));
			head = next_ls;
		}
		*lst = NULL;
	}
}
