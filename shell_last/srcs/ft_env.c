/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:23:51 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:07:17 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_env(void)
{
	ft_putendl_fd("minishell: env: No such file or directory", 2);
	g_data.n_exit = 127;
}

void	ft_env(void)
{
	int	i;

	i = 0;
	if (search_env("PATH") == -1)
	{
		error_env();
		return ;
	}	
	while (g_data.envp[i])
	{
		if (ft_strchr(g_data.envp[i], '='))
			printf("%s\n", g_data.envp[i]);
		i++;
	}
}
