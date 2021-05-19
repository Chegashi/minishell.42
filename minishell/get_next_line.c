/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 22:20:57 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/05/17 15:54:27 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#define BUFFER_SIZE 2048

int	check_save(char **save, char **line)
{
	char	*str;
	char	*tmp;

	str = NULL;
	if (*save)
	{
		str = ft_strchr(*save, '\n');
		if (str)
		{
			*str = '\0';
			*line = ft_strjoin(*line, *save);
			tmp = ft_strdup(++str);
			free(*save);
			*save = tmp;
			return (1);
		}
		else
		{
			*line = ft_strjoin(*line, *save);
			free(*save);
			*save = NULL;
		}
	}
	return (0);
}

int	check_error(int fd, char **line)
{
	char	c;

	if (fd < 0 || read(fd, &c, 0) < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	return (0);
}

int	free_return(char *buf, int b)
{
	free(buf);
	return (b);
}

int	norm_get_next(char **line, char **buf, int fd)
{
	*line = ft_strdup("");
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf && check_error(fd, line) == -1)
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buf;
	char		*str;
	int			ret;

	if (norm_get_next(line, &buf, fd) == -1)
		return (-1);
	if (check_save(&save, line) == 1)
		return (free_return(buf, 1));
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = '\0';
		str = ft_strchr(buf, '\n');
		if (str)
		{
			*str = '\0';
			save = ft_strdup(++str);
			*line = ft_strjoin(*line, buf);
			return (free_return(buf, 1));
		}
		*line = ft_strjoin(*line, buf);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (free_return(buf, 0));
}
