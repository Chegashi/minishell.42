/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:22:33 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 17:22:36 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_data.envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!g_data.envp)
		return ;
	i = 0;
	while (envp[i])
	{
		g_data.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_data.envp[i] = 0;
}
