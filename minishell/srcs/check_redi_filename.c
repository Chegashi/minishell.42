/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi_filename.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:40:05 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 15:22:36 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_file_dir(char *s)
{
	ft_putstr("minishell: ");
	ft_putstr(s);
	ft_putstr(" : No such file or directory\n");
	return (-1);
}

int	check_redi_filehelper(char **file, int i)
{
	if (ft_strlen(file[i]) == 0)
	{
		ft_putstr("minishell: syntax error near unexpected ");
		ft_putstr("token `newline'\n");
		return (-1);
	}
	if (found_redirection(file[i]))
	{
		if (check_parse_redir(file[i], 0, -1) == -1)
			return (-1);
		if (ft_strcmp(file[i], ">") == 0)
			parse_exterieur(1);
		else if (ft_strcmp(file[i], ">>") == 0)
			parse_exterieur(4);
		else if (ft_strcmp(file[i], "<") == 0)
			parse_inferieur(1);
		return (-1);
	}
	return (0);
}

int	check_redi_filename(t_pipes *pipes)
{
	int	i;

	i = 0;
	if (pipes->is_red == 0)
		return (0);
	while (pipes->type[i])
	{
		if (check_redi_filehelper(pipes->file, i) == -1)
			return (-1);
		if (ft_strcmp(pipes->type[i], ">") == 0)
			pipes->out = open(pipes->file[i],
					O_CREAT | O_TRUNC | O_WRONLY, 0664);
		else if (ft_strcmp(pipes->type[i], "<") == 0)
		{
			pipes->inp = open(pipes->file[i], O_RDONLY);
			if (pipes->inp < 0)
				return (no_file_dir(pipes->file[i]));
		}
		else if (ft_strcmp(pipes->type[i], ">>") == 0)
			pipes->out = open(pipes->file[i],
					O_CREAT | O_RDWR | O_APPEND, 0644);
		i++;
	}
	return (0);
}

int	ft_pipes_redir(t_pipes *pipes)
{
	t_pipes	*tmp;

	tmp = pipes;
	while (tmp)
	{
		if (check_redi_filename(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
