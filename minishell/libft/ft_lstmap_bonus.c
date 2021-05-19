/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:17:35 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/22 22:24:02 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list *new_list;
	t_list *current;
	t_list *node;

	if (!lst || !del || !f)
		return (NULL);
	current = lst;
	new_list = ft_lstnew(f(current->content));
	while (current->next != NULL)
	{
		current = current->next;
		if (!(node = ft_lstnew(f(current->content))))
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, node);
	}
	return (new_list);
}
