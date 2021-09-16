/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:52:54 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:07:59 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_size(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

void	remove_from_env(int index, char **envp)
{
	char	**tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = env_size(envp);
	tmp = (char **)malloc(sizeof(char *) * size);
	while (envp[i])
	{
		if (i != index)
		{
			tmp[j] = ft_strdup(envp[i]);
			add_to_mem(&g_data.mem, envp[i]);
			j++;
		}
		else
			add_to_mem(&g_data.mem, envp[i]);
		i++;
	}
	tmp[j] = 0;
	free(g_data.envp);
	g_data.envp = tmp;
}

void	msg_error_unset(char *msg, char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	write(2, str, ft_strlen(str));
	write(2, msg, ft_strlen(msg));
	g_data.n_exit = 1;
}

int	is_error_unset(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '"' && str[i] != '\'')
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) || ft_isalpha(str[i])
			|| str[i] == '"' || str[i] == '\'' || str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_unset(char **params)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (!params[1])
		return ;
	while (params[i])
	{
		if (is_error_unset(params[i]))
		{
			msg_error_unset("': not a valid identifier\n", params[i]);
			i++;
			continue ;
		}
		k = search_env(params[i]);
		if (k != -1)
			remove_from_env(k, g_data.envp);
		else if (ft_isdigit(params[i][0]))
			msg_error_unset("': not a valid identifier\n", params[i]);
		i++;
	}
}
