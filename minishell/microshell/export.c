/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:30:25 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/01 21:17:03 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

// void	__export(char *str, t_v_env **head)
// {
// 	t_v_env	*iter;
// 	t_v_env	*next;
// 	char	*key;
// 	int		is_defined;

// 	iter = *head;
// 	is_defined = 0;
// 	key = key_from_str(str);
// 	while(iter->next)
// 	{
// 		if (!ft_strcmp(key, iter->next->key))
// 		{
// 			is_defined = 1;
// 			free(iter->value);
// 			iter->value = ft_strdup(value);
// 			return ;
// 		}
// 		iter = iter->next;	
// 	}
// 	if (!is_defined)
// 		iter->next = str_to_v_env(str);
// }

