/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:43:26 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 17:43:28 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_rm_q(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			i++;
		else if (line[i] == '\'')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*remove_quote(char *line, int i, int j)
{
	char	*str;

	str = (char *)malloc(size_rm_q(line) + 1);
	while (line[i])
	{
		if (line[i] == '"')
		{
			str[j] = line[++i];
			while (line[i] != '"' && line[i])
				str[++j] = line[++i];
			str[j] = line[++i];
		}
		else if (line[i] == '\'')
		{
			str[j] = line[++i];
			while (line[i] != '\'' && line[i])
				str[++j] = line[++i];
			str[j] = line[++i];
		}
		else
			str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}
