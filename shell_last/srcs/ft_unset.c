/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:47:09 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 17:53:45 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_dil(char *str, char d)
{
	char	*s;

	s = str;
	while (*str && *str != d)
		str++;
	return (str - s);
}

char	*value_from_str(char *str)
{
	int		len_value;
	char	*value;
	int		i;

	i = -1;
	len_value = ft_strlen_dil(str, '=');
	value = (char *)malloc(sizeof(char) * (len_value + 1));
	if (!value)
		return (NULL);
	while (++i < len_value)
		value[i] = str[i];
	value[i] = 0;
	return (value);
}

char	*key_from_str(char *str)
{
	int		len_key;
	char	*key;
	int		i;

	i = -1;
	len_key = ft_strlen_dil(str, '=');
	key = (char *)malloc(sizeof(char) * (len_key + 1));
	if (!key)
		return (NULL);
	while (++i < len_key)
		key[i] = str[i];
	key[i] = 0;
	return (key);
}

int	search_env(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (g_data.envp[i])
	{
		key = key_from_str(g_data.envp[i]);
		add_to_mem(&g_data.mem, key);
		if (ft_strcmp(key, str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free_array(char **tbl)
{
	int	i;

	if (!tbl)
		return ;
	i = 0;
	while (tbl[i] != NULL)
	{
		free(tbl[i]);
		i++;
	}
	free(tbl);
}
