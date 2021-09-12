/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:40:41 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:03:36 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_size_space(char *s, int i, int size)
{
	if (s[i - 1] && s[i - 1] != '>'
		&& s[i - 1] != '<' && s[i - 1] != ' ')
		size++;
	if (s[i + 1] && s[i + 1] != '>'
		&& s[i + 1] != '<' && s[i + 1] != ' ')
		size++;
	return (size);
}

int	cnt_red(char *s, int size)
{
	int	i;
	int	q;

	q = 0;
	i = 0;
	size = ft_strlen(s);
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && !q)
			q = 1;
		else if ((s[i] == '\"' || s[i] == '\'') && q)
			q = 0;
		if (s[i] == '>' && s[i + 1] == '>' && !q)
			size = count_size_space(s, i, size);
		else if ((s[i] == '>' || s[i] == '<') && !q)
			size = count_size_space(s, i, size);
		i++;
	}
	return (size);
}

void	split_redir_help1(t_split *split, char *line)
{
	if (line[split->i - 1] && line[split->i - 1] != '>'
		&& line[split->i - 1] != '<' && line[split->i - 1] != ' ')
		split->str[split->j++] = ' ';
	split->str[split->j++] = line[split->i];
	split->str[split->j++] = line[split->i++];
	if (line[split->i + 1] && line[split->i + 1] != '>'
		&& line[split->i + 1] != '<' && line[split->i + 1] != ' ')
		split->str[split->j++] = ' ';
}

void	split_redir_help2(t_split *split, char *line)
{
	if (line[split->i - 1] && line[split->i - 1] != '>'
		&& line[split->i - 1] != '<' && line[split->i - 1] != ' ')
		split->str[split->j++] = ' ';
	split->str[split->j++] = line[split->i];
	if (line[split->i + 1] && line[split->i + 1] != '>'
		&& line[split->i + 1] != '<' && line[split->i + 1] != ' ')
		split->str[split->j++] = ' ';
}

char	*split_redirection(char *line)
{
	t_split	split;

	split.q = 0;
	split.i = 0;
	split.j = 0;
	split.str = (char *)malloc(sizeof(char) * (cnt_red(line, 0) + 1));
	while (line[split.i])
	{
		if ((line[split.i] == '\"' || line[split.i] == '\'') && !split.q)
			split.q = 1;
		else if ((line[split.i] == '\"' || line[split.i] == '\'') && split.q)
			split.q = 0;
		if (line[split.i] == '>' && line[split.i + 1] == '>' && !split.q)
			split_redir_help1(&split, line);
		else if ((line[split.i] == '>' || line[split.i] == '<') && !split.q)
			split_redir_help2(&split, line);
		else
			split.str[split.j++] = line[split.i];
		split.i++;
	}
	split.str[split.j] = '\0';
	free(line);
	return (split.str);
}
