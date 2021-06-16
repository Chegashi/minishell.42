/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:41:11 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:26:32 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	found_in_useless(int *nb, int c)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (c == nb[i] || c == nb[i] + 1)
			return (1);
		i++;
	}
	return (0);
}

char	**remove_useless(t_pipes *pipes, int *nb)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size_params(pipes->params) + 1));
	if (tmp == 0)
		return (pipes->params);
	while (pipes->params[i])
	{
		if (found_in_useless(nb, i) == 0)
		{
			tmp[j] = ft_strdup(pipes->params[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	ft_redir_helper(t_pipes *pipes, int i, int *count, int j)
{
	while (pipes->params[i])
	{
		if (found_redirection(pipes->params[i]))
		{
			if (check_not_qt(pipes->params, i) == 0)
			{
				pipes->type[j] = ft_strdup(pipes->params[i]);
				pipes->nb_useless[j] = i;
				(*count)++;
				if (pipes->params[i + 1])
				{
					pipes->file[j] = ft_strdup(pipes->params[i + 1]);
					(*count)++;
				}
				else
					pipes->file[j] = ft_strdup("");
				j++;
			}
		}
		i++;
	}
	pipes->file[j] = NULL;
	pipes->type[j] = NULL;
}

void	ft_redirection(t_pipes *pipes)
{
	int		i;
	int		count;
	int		j;

	j = 0;
	count = count_redir(pipes->params) + 1;
	i = 0;
	pipes->file = (char **)malloc(sizeof(char *) * (count));
	if (pipes->file == 0)
		return ;
	pipes->type = (char **)malloc(sizeof(char *) * (count));
	if (pipes->type == 0)
		return ;
	pipes->nb_useless = (int *)malloc(sizeof(int *) * count_redir(pipes->params));
	if (count > 1)
	{
		count = 0;
		pipes->is_red = 1;
		ft_redir_helper(pipes, i, &count, j);
		pipes->params = remove_useless(pipes, pipes->nb_useless);
	}
	if (pipes->nb_useless)
	{
		free(pipes->nb_useless);
		pipes->nb_useless = NULL;
	}
}
