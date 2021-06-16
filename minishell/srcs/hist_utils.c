/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:27:15 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_hist	*ft_histlast(t_hist *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

int 	ft_histsize(t_hist *lst)
{
	int	l;

	l = 0;
	while (lst)
	{
		l++;
		lst = lst->next;
	}
	return (l);
}

t_hist	*ft_histnew(char *line)
{
	t_hist	*list;

	list = NULL;
	list = (t_hist *)malloc (sizeof (t_hist));
	list->line = line;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	ft_histadd_front(t_hist **alst, t_hist *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}
