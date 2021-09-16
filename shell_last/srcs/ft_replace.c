/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:56:18 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:55:59 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_replace(char *str, char *sub, char *rpl, int i)
{
	t_replace	r;

	r.new = ft_strdup(str);
	r.sub_l = ft_strlen(sub);
	r.rp_l = ft_strlen(rpl);
	if (sub == NULL || rpl == NULL)
		return (r.new);
	r.tmp = ft_strstr(r.new, sub);
	while (r.tmp && i != 1)
	{
		r.old = r.new;
		r.old_l = ft_strlen(r.old);
		r.new = (char *)malloc(sizeof(char) * (r.old_l - r.sub_l + r.rp_l + 1));
		ft_memcpy(r.new, r.old, r.tmp - r.old);
		ft_memcpy(r.new + (r.tmp - r.old), rpl, r.rp_l);
		ft_memcpy(r.new + (r.tmp - r.old) + r.rp_l,
			r.tmp + r.sub_l, r.old_l - r.sub_l - (r.tmp - r.old));
		ft_memset(r.new + r.old_l - r.sub_l + r.rp_l, 0, 1);
		free(r.old);
		r.tmp = ft_strstr(r.new, sub);
		i++;
	}
	return (r.new);
}
