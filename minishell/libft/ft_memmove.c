/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:37:15 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/23 15:43:43 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*str_copy(unsigned char *dest, unsigned char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	return (dest);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*str;

	dest = (unsigned char*)dst;
	str = (unsigned char*)src;
	i = 0;
	if ((!dest && !str) || dest == str)
		return (dst);
	if (str < dest)
	{
		while (i < len)
		{
			dest[len - i - 1] = str[len - i - 1];
			i++;
		}
	}
	else
	{
		str_copy(dest, str, len);
	}
	return (dst);
}
