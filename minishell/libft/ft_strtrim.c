/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:12:11 by nbjaghou          #+#    #+#             */
/*   Updated: 2019/10/23 20:16:16 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_char(int c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == (char)c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		count;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	count = 0;
	while (find_char(s1[start], set))
		start++;
	while (find_char(s1[end - 1], set) && end > start)
		end--;
	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (count < (end - start))
	{
		str[count] = (char)s1[count + start];
		count++;
	}
	str[count] = '\0';
	return (str);
}
