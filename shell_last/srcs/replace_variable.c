/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 21:14:29 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 18:15:37 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_variable(char *var)
{
	int		i;
	char	*str;
	char	*key;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	if (*var)
		var++;
	while (g_data.envp[i])
	{
		key = key_from_str(g_data.envp[i]);
		add_to_mem(&g_data.mem, key);
		if (ft_strcmp(key, var) == 0)
		{
			tmp = str;
			str = ft_strdup(g_data.envp[i] + ft_strlen(key) + 1);
			free(tmp);
			return (str);
		}	
		i++;
	}
	return (str);
}

int	is_just_dollar(char *var)
{
	int	i;

	i = 0;
	if (var[1] && !ft_isalpha(var[1]) && !ft_isdigit(var[1]))
		return (1);
	while (var[i])
	{
		if (var[i] != '$')
			return (0);
		else
			i++;
	}
	return (1);
}

int	is_in_sq(char *str, int i)
{
	int	q;

	q = 0;
	if (str[i] == '\'' && str[i + 1] != '\'')
		return (1);
	return (0);
}

int	replace_variable2(int i, char *str, char *var, char **line)
{
	char	*value;
	char	*tmp;

	var = ft_substr(str, 0, i);
	add_to_mem(&g_data.mem, var);
	if (is_just_dollar(var) == 0)
	{
		value = get_variable(var);
		tmp = str_replace(*line, var, value);
		if (!is_in_sq(tmp, i))
		{
			add_to_mem(&g_data.mem, *line);
			*line = tmp;
		}
		else
			free(tmp);
		free(value);
	}
	return (i);
}

char	*replace_variable(char *line)
{
	char	*str;
	char	*var;
	int		i;

	str = ft_strdup(line);
	add_to_mem(&g_data.mem, str);
	while (str)
	{
		str = ft_strchr(str, '$');
		if (str)
		{
			i = 1;
			if (ft_isdigit(str[i]))
				i++;
			else
			{
				while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i])))
					i++;
			}
			i = replace_variable2(i, str, var, &line);
			str += i;
		}
	}
	return (line);
}
