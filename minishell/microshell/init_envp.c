/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:40:02 by mochegri          #+#    #+#             */
/*   Updated: 2021/06/30 20:20:47 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

t_var     *init_envp(char **env)
{
	t_var		*head;
    t_var       *iter;

	head = (t_var *) malloc(sizeof(t_var));
	if (!head)
		return (NULL);
	ft_fill_var(&head, (*env)++);
	while(*env)
	{
		iter->next = (t_var *) malloc(sizeof(t_var));
		if (!iter->next)
		return (NULL);
		iter = iter->next;
		ft_fill_var(&(iter->next), (*env)++);
	}
	return (head);
}

void	ft_fill_var(t_var **var, char *str)
{
	(*var)->key = ft_get_key(str);
	(*var)->value = ft_get_value(str);
	(*var)->next = NULL;
}

char *ft_get_key(char *str)
{
	int		len;
	char	*key;

	len = -1;
	while (str[++len] && str[len] != '=')
		;
	key = (char*)malloc(sizeof(char) * len);
	ft_strncpy(key, str, len);
	return (key);
}

char	*ft_get_value(char *str)
{
	int		len;
	char	*value;
	int is_var;

	len = -1;
	is_var = 0;
	while (*str && *str == '=')
		str++;
	if (*str++ == '$')
		is_var = 1;
	while (str[++len] && str[len] != '=')
		;
	len = -1;
	value = (char*)malloc(sizeof(char) * len);
	ft_strncpy(value, str, len);
	if (is_var)
		return(ft_get_value(value));
	else
		return (value);
}

// void export(t_var *var, char *str)
// {
// 	t_var	*iter;

// 	iter = var;
// 	while (var && iter->next)
// 		iter = iter->next;
// 	iter->next = (t_var *) malloc(sizeof(t_var));
// 	ft_fill_vars(iter->next, str);
// }

// void ft_unset(t_var *var, char *key)
// {
// 	t_var	*iter;
// 	t_var	*tmp;
// 	char	*iter_key;

// 	iter = var;
// 	while (iter && ft_strcmp(iter->key,key))
// 		iter = iter->next;
// 	tmp = iter;
// 	iter = iter->next;
// 	free(iter->key);
// 	free(iter->value);
// 	free(iter);
// }

// void	ft_get_value(t_var *var, char *key)
// {
// 	t_var	*iter;

// 	iter = var;
// 	while (iter && ft_strcmp(iter->key,key))
// 		iter = iter->next;
// 	if (ft_strcmp(iter->key,key))
// 		return (iter->value);
		
// }

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (!src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}