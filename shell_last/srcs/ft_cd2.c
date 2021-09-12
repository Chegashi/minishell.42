/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 13:20:38 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:26:27 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pwd(char *key, char *pwd)
{
	char	*tmp;

	if (search_env(key) != -1)
		edit_envp(key, pwd);
	else
	{
		tmp = ft_strjoin(key, "=");
		add_to_mem(&g_data.mem, tmp);
		tmp = ft_strjoin(tmp, pwd);
		add_to_env(tmp, g_data.envp);
		free(tmp);
	}
}
