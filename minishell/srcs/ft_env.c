/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:50 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/02 13:15:23 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_v_env *head)
{
	t_v_env   *iter;

	iter = head;
	while(iter)
	{
		ft_putstr(iter->key);
		write(1, "\n", 1);
		ft_putstr(iter->value);
		iter = iter->next;
	}
}

t_v_env	*str_to_v_env(char *str)
{
	t_v_env	*var;

	var = (t_v_env *)malloc(sizeof(t_v_env));
	var->key = key_from_str(str);
	var->value = value_from_str(str + ft_strlen_dil(var->key, 0) + 1);
	if (!var)
		return (NULL);	
	var->next = NULL;
	return (var);
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

int	ft_strlen_dil(char *str, char d)
{
	char	*s;

	s = str;
	while (*str && *str != d)
		str++;
	return (str - s);
}

t_v_env	*init_envp(char **envp)
{
	t_v_env	*head;
	t_v_env	*iter;

	head = NULL;
	while (*envp)
	{
		if (!head)
		{
			head = str_to_v_env(*envp++);
			iter = head;
			continue ;
		}
		iter->next = str_to_v_env(*envp++);
		iter = iter->next;
	}
	return (head);
}

char	*get_value(char *key, t_v_env *head)
{
	t_v_env   *iter;

	iter = head;
	while(iter)
	{
		if (!ft_strcmp(iter->key, key))
			return (iter->value);
		iter = iter->next;
	}
	return ("");
}
