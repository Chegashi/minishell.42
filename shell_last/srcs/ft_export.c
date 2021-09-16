/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:48:53 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/09/16 17:08:19 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_str_error(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = key_from_str(str);
	add_to_mem(&g_data.mem, key);
	if (!ft_isalpha(key[i]) && key[i] != '_' && str[i] != '"' && str[i] != '\'')
		return (1);
	while (key[i])
	{
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '='
			|| key[i] == '"' || key[i] == '\'' || key[i] == '_')
			i++;
		else if (key[i + 1] == '\0' && key[i] == '+')
			i++;
		else
			return (1);
	}
	return (0);
}

void	add_to_env(char *str, char **envp)
{
	char	**tmp;
	int		size;
	int		i;

	i = 0;
	size = env_size(envp);
	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		add_to_mem(&g_data.mem, envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = 0;
	free(g_data.envp);
	g_data.envp = tmp;
}

char	**sort_envp_alpha(char **envp, int i, int j)
{
	int		size;
	char	*tmp;

	size = env_size(envp);
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				add_to_mem(&g_data.mem, envp[j]);
				tmp = ft_strdup(envp[j]);
				add_to_mem(&g_data.mem, envp[j + 1]);
				envp[j] = ft_strdup(envp[j + 1]);
				add_to_mem(&g_data.mem, tmp);
				envp[j + 1] = ft_strdup(tmp);
			}
			j++;
		}
		i++;
	}
	return (envp);
}

void	read_export(char **envp)
{
	char	**tmp;
	int		i;
	char	*key;
	char	*var;

	i = 0;
	tmp = sort_envp_alpha(envp, 0, 0);
	while (tmp[i])
	{
		key = key_from_str(tmp[i]);
		add_to_mem(&g_data.mem, key);
		var = tmp[i] + ft_strlen(key) + 1;
		printf("declare -x %s", key);
		if (ft_strlen(var) > 0 || ft_strchr(tmp[i], '='))
			printf("=\"%s\"\n", var);
		else
			printf("\n");
		i++;
	}
}

void	msg_error_export(char *msg, char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	write(2, str, ft_strlen(str));
	write(2, msg, ft_strlen(msg));
	g_data.n_exit = 1;
}
