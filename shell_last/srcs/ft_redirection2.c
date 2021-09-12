/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:11:55 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:46:23 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redir_helper(t_pipes *pipes, int i, int j)
{
	char	*tmp;

	while (pipes->params[i])
	{
		if (found_redirection(pipes->params[i])
			&& check_not_qt(pipes->params, i) == 0)
		{
			pipes->type[j] = pipes->params[i];
			pipes->nb_useless[j] = i + 1;
			if (pipes->params[i + 1])
				pipes->file[j] = pipes->params[i + 1];
			else
			{
				tmp = ft_strdup(" ");
				pipes->file[j] = tmp;
				add_to_mem(&g_data.mem, tmp);
			}
			j++;
		}
		i++;
	}
	pipes->file[j] = NULL;
	pipes->type[j] = NULL;
}

int	check_redi_file2(t_pipes *pipes, int i)
{
	if (ft_strcmp(pipes->type[i], ">") == 0)
		pipes->out = open(pipes->file[i], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else if (ft_strcmp(pipes->type[i], "<") == 0)
	{
		pipes->inp = open(pipes->file[i], O_RDONLY);
	}
	else if (ft_strcmp(pipes->type[i], ">>") == 0)
		pipes->out = open(pipes->file[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strcmp(pipes->type[i], "<<") == 0)
	{
		ft_heredoc(pipes->file[i]);
		pipes->inp = open("/goinfre/nbjaghou/tmp", O_RDONLY);
	}
	if (pipes->inp < 0)
		return (no_file_dir(pipes->file[i]));
	else if (pipes->out < 0)
		return (no_file_dir(pipes->file[i]));
	return (0);
}

int	check_redi_filehelper(char **file, int i)
{
	if (ft_strcmp(file[i], " ") == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
		return (-1);
	}
	if (found_redirection(file[i]))
	{
		if (ft_strcmp(file[i], ">") == 0)
			parse_exterieur(1);
		else if (ft_strcmp(file[i], ">>") == 0)
			parse_exterieur(4);
		else if (ft_strcmp(file[i], "<") == 0)
			parse_inferieur(1);
		else if (ft_strcmp(file[i], "<<") == 0)
			parse_inferieur(5);
		return (-1);
	}
	return (0);
}

int	check_redi_filename(t_pipes *pipes, int i)
{
	while (pipes->type[i])
	{
		if (check_redi_filehelper(pipes->file, i) == -1)
			return (-1);
		if (check_redi_file2(pipes, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_redirection(t_pipes *pipes)
{
	int	count;

	count = count_redir(pipes->params) + 1;
	pipes->type = (char **)malloc(sizeof(char *) * (count));
	pipes->file = (char **)malloc(sizeof(char *) * (count));
	pipes->nb_useless = (int *)malloc(sizeof(int *) * (count - 1));
	ft_redir_helper(pipes, 0, 0);
	free(pipes->params);
	pipes->params = remove_useless(pipes, pipes->nb_useless);
	g_data.error = check_redi_filename(pipes, 0);
	free(pipes->type);
	free(pipes->file);
	free(pipes->nb_useless);
}
