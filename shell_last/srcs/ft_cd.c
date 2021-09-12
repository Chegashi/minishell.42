/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:22:48 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:26:24 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg_error_cd(char *msg)
{
	write(2, "bash: cd: ", 11);
	write(2, msg, ft_strlen(msg));
}

void	msg_error_cd2(char *msg, char *str)
{
	write(2, "bash: cd: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 3);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 2);
	g_data.n_exit = 1;
}

int	edit_envp(char *var, char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (g_data.envp[i])
	{
		key = key_from_str(g_data.envp[i]);
		add_to_mem(&g_data.mem, key);
		if (ft_strcmp(key, var) == 0)
		{
			add_to_mem(&g_data.mem, g_data.envp[i]);
			g_data.envp[i] = ft_strjoin(key, "=");
			add_to_mem(&g_data.mem, g_data.envp[i]);
			g_data.envp[i] = ft_strjoin(g_data.envp[i], str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_cd2(char *tmp, char *pwd, char *old_pwd, char *params)
{
	if (tmp && ft_strlen(tmp) == 0)
		return ;
	if (!chdir(tmp))
	{
		if (!getcwd(pwd, MAX_PATH))
			ft_putendl_fd(strerror(errno), 1);
		add_pwd("PWD", pwd);
		add_pwd("OLDPWD", old_pwd);
		g_data.n_exit = 0;
		return ;
	}
	else
	{
		msg_error_cd2(strerror(errno), params);
		return ;
	}
}

void	ft_cd(char **params)
{
	char	pwd[MAX_PATH];
	char	old_pwd[MAX_PATH];
	char	*tmp;

	if (!getcwd(old_pwd, MAX_PATH))
		ft_putendl_fd(strerror(errno), 1);
	tmp = params[1];
	if (!tmp || (tmp && ft_strcmp(params[1], "~") == 0))
	{
		tmp = change_plus_envp("HOME");
		add_to_mem(&g_data.mem, tmp);
		if (!tmp || ft_strlen(tmp) == 0)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_data.n_exit = 1;
			return ;
		}
	}
	ft_cd2(tmp, pwd, old_pwd, params[1]);
}
