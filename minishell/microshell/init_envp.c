/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:40:02 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/02 08:57:16 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

t_v_env	*str_to_v_env(char *str)
{
	t_v_env	*var;

	var = (t_v_env *)malloc(sizeof(t_v_env));
	var->key = key_from_str(str);
	var->value = value_from_str(str);
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
	len_value = ft_strlen_dil(str, '=', ' ');
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
	len_key = ft_strlen_dil(str, '=', 0);
	key = (char *)malloc(sizeof(char) * (len_key + 1));
	if (!key)
		return (NULL);
	while (++i < len_key)
		key[i] = str[i];
	key[i] = 0;
	return (key);
}

int	ft_strlen_dil(char *str, char d, char d2)
{
	char	*s;

	s = str;
	while (*str && *str != d && *str != d2)
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

void	__env__(t_v_env *head)
{
	t_v_env   *iter;

	iter = head;
	while(iter)
	{
		printf("%s=%s\n", iter->key, iter->value);
		iter = iter->next;
	}
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
