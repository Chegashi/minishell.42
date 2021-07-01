/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:27:54 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/01 19:28:22 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	__unset(char *key, t_v_env **head)
{
	t_v_env	*iter;
	t_v_env	*to_delete;
	t_v_env	*next;

	iter = *head;
	while(iter)
	{
		if (!ft_strcmp(key, iter->next->key))
		{
			to_delete = iter->next;
			iter->next = iter->next->next;
			free(to_delete->key);
			free(to_delete->value);
			iter = iter->next->next;
			free(to_delete);
			return ;
		}
		iter = iter->next;	
	}
}
