/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 21:22:20 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/01 21:25:39 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	if ((s1[i] != '\0' && s2[i] == '\0') || ((s1[i] == '\0' && s2[i] != '\0')))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	word_nbr( char *s, char c)
{
	int	count;

	count = 0;
	if (*s)
		count++;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int	len_wrd( char *s, char c)
{
	char	*len;

	len = s;
	while (*len && *len != c)
		len++;
	return (len - s);
}

void	*ft_free_mem(char **wrds, int j)
{
	while (j--)
		free(wrds[j]);
	free(wrds);
	return (NULL);
}

char	**ft_fill(char *s, char c, char **wrds)
{
	int	j;
	int	k;
	int	nbr_word;

	j = -1;
	nbr_word = word_nbr(s, c);
	while (*s && ++j < nbr_word)
	{
		while (*s == c)
			s++;
		k = 0;
		wrds[j] = malloc(sizeof(char) * (len_wrd(s, c) + 1));
		if (wrds[j] == NULL)
			return (ft_free_mem(wrds, j));
		while (*s && *s != c)
			wrds[j][k++] = *s++;
		wrds[j][k] = 0;
	}
	wrds[j] = 0;
	return (wrds);
}

char	**ft_split(char *s, char c)
{
	char	**wrds;

	if (!s)
		return (NULL);
	wrds = malloc(sizeof(char *) * word_nbr(s, c) + 1);
	if (!wrds)
		return (NULL);
	return (ft_fill(s, c, wrds));
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			ft_putchar(str[i]);
			i++;
		}
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}