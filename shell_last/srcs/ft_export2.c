/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:55:00 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/12 16:47:38 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_added_var(char *key)
{
	int	i;

	i = ft_strlen(key);
	if (key[i - 1] == '+')
		return (1);
	return (0);
}

char	*change_plus_envp(char *str)
{
	int		i;
	char	*key;
	char	*var;
	char	*tmp;

	i = 0;
	var = ft_strdup("");
	while (g_data.envp[i])
	{
		key = key_from_str(g_data.envp[i]);
		add_to_mem(&g_data.mem, key);
		if (ft_strcmp(key, str) == 0)
		{
			tmp = var;
			var = ft_substr(g_data.envp[i],
					ft_strlen(key) + 1, ft_strlen(g_data.envp[i]));
			free(tmp);
			break ;
		}
		i++;
	}
	return (var);
}

void	ft_export3(char *key, char *str, char *var)
{
	char	*tmp;

	if (search_env(key) != -1)
	{
		if (ft_strchr(str, '='))
			edit_envp(key, var);
	}
	else
	{
		if (ft_strchr(str, '='))
		{
			tmp = ft_strjoin(key, "=");
			add_to_mem(&g_data.mem, tmp);
			tmp = ft_strjoin(tmp, var);
		}
		else
			tmp = ft_strdup(key);
		add_to_env(tmp, g_data.envp);
		free(tmp);
	}
}

void	ft_export2(char *key, char *str, char *var)
{
	char	*tmp;

	if (is_added_var(key))
	{
		key = ft_substr(key, 0, ft_strlen(key) - 1);
		add_to_mem(&g_data.mem, key);
		tmp = change_plus_envp(key);
		var = ft_strjoin(tmp, var);
		add_to_mem(&g_data.mem, var);
		free(tmp);
	}
	ft_export3(key, str, var);
}

void	ft_export(t_pipes *pipe, int i)
{
	char	*key;
	char	*var;
	char	*str;

	if (!pipe->params[1])
	{
		read_export(g_data.envp);
		return ;
	}
	while (pipe->params[i])
	{
		str = remove_quote(pipe->params[i], 0, 0);
		if (ft_strlen(str) > 0)
		{
			if (!export_str_error(str))
			{
				key = key_from_str(str);
				add_to_mem(&g_data.mem, key);
				var = str + ft_strlen(key) + 1;
				ft_export2(key, str, var);
			}
			else
				msg_error_export("': not a valid identifier\n", str);
		}
		free(str);
		i++;
	}
}

