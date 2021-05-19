/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:03:24 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/21 19:56:25 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*str;
	int			i;

	i = 0;
	dest = (char*)dst;
	str = (const char*)src;
	if (!dest && !str)
		return (NULL);
	while (n--)
	{
		dest[i] = str[i];
		i++;
	}
	return (dst);
}
