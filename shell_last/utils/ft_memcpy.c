/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:03:24 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/02/05 14:51:38 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*str;
	int			i;

	i = 0;
	dest = (char *)dst;
	str = (const char *)src;
	if (!dest && !str)
		return (NULL);
	while (n--)
	{
		dest[i] = str[i];
		i++;
	}
	return (dst);
}
