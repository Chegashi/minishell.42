/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:33:49 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/23 15:40:18 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dig(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (n + 1);
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	sign_digit(int n)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	return (sign);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nb;

	i = 0;
	nb = n;
	i = count_dig(nb);
	if ((str = (char*)malloc(sizeof(char) * (i + 1))) == 0)
		return (NULL);
	str[i--] = '\0';
	if (nb < 0)
		nb = nb * (-1);
	while (i >= 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	if (sign_digit(n) == -1)
		str[0] = '-';
	return (str);
}
