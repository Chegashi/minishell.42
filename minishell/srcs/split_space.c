/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:40:51 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	size_tab(char const *s)
{
	int	count;
	int	i;
	int	q;

	q = 0;
	count = 0;
	i = skip_space(s, 0);
	while (s[i])
	{
		while (s[i])
		{
			if ((s[i] == '\'' || s[i] == '\"') && !q)
				q = 1;
			else if ((s[i] == '\'' || s[i] == '\"') && q)
				q = 0;
			else if (check_space(s[i]) && !q)
				break ;
			i++;
		}
		count++;
		i = skip_space(s, i);
	}
	return (count);
}

static int	size_word(char const *s)
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
		else if (check_space(s[i]) && !q)
			break ;
		i++;
	}
	return (i);
}

static int	skip_word(char const *s)
{
	int	i;

	i = 0;
	while (check_space(s[i]) && s[i])
		i++;
	return (i);
}

char	**splite_space(char const *s)
{
	char	**tabl;
	size_t	i;
	size_t	count;

	count = size_tab(s);
	i = 0;
	tabl = (char **)malloc(sizeof(char *) * (count + 1));
	if (tabl == 0)
		return (NULL);
	while (i < count)
	{
		s = s + skip_word(s);
		tabl[i] = ft_substr(s, 0, size_word(s));
		if (tabl[i] == 0)
			return (free_table(tabl, i));
		i++;
		s = s + size_word(s);
	}
	tabl[i] = NULL;
	return (tabl);
}
