/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:13:53 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/09 16:13:55 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_char(char c, char const *s, int i)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	size_tab(char const *s, char c)
{
	int	count;
	int	i;
	int	q;

	count = 0;
	q = 0;
	i = skip_char(c, s, 0);
	while (s[i])
	{
		while (s[i])
		{
			if ((s[i] == '\'' || s[i] == '\"') && !q)
				q = 1;
			else if ((s[i] == '\'' || s[i] == '\"') && q)
				q = 0;
			else if (s[i] == c && !q)
				break ;
			i++;
		}
		count++;
		i = skip_char(c, s, i);
	}
	return (count);
}

static int	size_word(char const *s, char c)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !q)
			q = 1;
		else if ((s[i] == '\'' || s[i] == '\"') && q)
			q = 0;
		else if (s[i] == c && !q)
			break ;
		i++;
	}
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

char	**cmd_split(char const *s, char c)
{
	char	**tabl;
	size_t	i;
	size_t	count;

	count = size_tab(s, c);
	i = 0;
	tabl = (char **)malloc(sizeof(char *) * (count + 1));
	if (tabl == 0)
		return (NULL);
	while (i < count)
	{
		s = s + skip_word(s, c);
		tabl[i] = ft_substr(s, 0, size_word(s, c));
		if (tabl[i] == 0)
			return (free_table(tabl, i));
		i++;
		s = s + size_word(s, c);
	}
	tabl[i] = NULL;
	return (tabl);
}
