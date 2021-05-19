/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:23:12 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/16 13:21:12 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*head;
	int		i;

	head = NULL;
	i = 0;
	if (!lst)
		return (NULL);
	while (i < ft_lstsize(lst))
	{
		lst = lst->next;
		i++;
	}
	head = lst;
	return (head);
}
