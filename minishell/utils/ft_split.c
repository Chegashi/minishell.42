/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:41:05 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 17:32:28 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	size_tab(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static int	size_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static int	skip_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

static char	**free_table(char **tab, int j)
{
	while (j--)
		free(tab[j]);
	free(tab);
	tab = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	count;

	count = size_tab(s, c);
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (tab == 0)
		return (NULL);
	while (i < count)
	{
		s = s + skip_word(s, c);
		tab[i] = ft_substr(s, 0, size_word(s, c));
		if (tab[i] == 0)
			return (free_table(tab, i));
		i++;
		s = s + size_word(s, c);
	}
	tab[i] = NULL;
	return (tab);
}
