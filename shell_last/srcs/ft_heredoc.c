/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:45:35 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/27 18:46:09 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_params(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	found_in_useless(int *nb, int c)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (c == nb[i] || c == nb[i] - 1)
			return (1);
		i++;
	}
	return (0);
}

char	**remove_useless(t_pipes *pipes, int *nb)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size_params(pipes->params) + 1));
	if (tmp == 0)
		return (pipes->params);
	while (pipes->params[i])
	{
		add_to_mem(&g_data.mem, pipes->params[i]);
		if (found_in_useless(nb, i) == 0)
		{
			tmp[j] = ft_strdup(pipes->params[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int	no_file_dir(char *s)
{
	ft_putstr("bash: ");
	ft_putstr(s);
	ft_putstr(": ");
	ft_putendl_fd(strerror(errno), 2);
	g_data.n_exit = 1;
	return (-1);
}

void	ft_heredoc(char *name)
{
	char	*buf;
	char	*line;
	int		fd;
	char	*tmp;

	line = ft_strdup("");
	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(buf, name) == 0)
			break ;
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		free(buf);
	}
	free(buf);
	fd = open("/goinfre/nbjaghou/tmp", O_CREAT | O_TRUNC | O_WRONLY, 0664);
	write(fd, line, ft_strlen(line));
	free(line);
	close(fd);
}
