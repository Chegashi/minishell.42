/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:04:19 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 16:57:36 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	free_hist(t_hist *hist)
{
	t_hist	*tmp;

	tmp = hist;
	if (tmp == NULL)
		return ;
	while (hist)
	{
		if (tmp->line)
			ft_free(tmp->line);
		tmp = hist;
		hist = hist->next;
		free(tmp);
	}
	hist = NULL;
}

void	ft_free(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
}
