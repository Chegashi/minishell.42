/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:28:10 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/21 16:31:59 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(const char *s, int c)
{
	int	i;
	int count;

	i = ft_strlen(s) + 1;
	count = 0;
	while (i--)
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	return (count);
}

char		*ft_strrchr(const char *s, int c)
{
	int i;
	int count;

	count = count_c(s, c);
	i = ft_strlen(s) + 1;
	while (i--)
	{
		if (*s == (char)c)
		{
			if (count == 1)
				return ((char*)s);
			else
				count--;
		}
		s++;
	}
	return (0);
}
