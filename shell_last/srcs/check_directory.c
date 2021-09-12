/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:26:25 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:43:50 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_directory(char *cmd)
{
	int			fd;
	struct stat	stats;

	fd = open(cmd, O_RDONLY);
	if (fd < 0)
	{
		error_no_file(cmd);
		return (0);
	}
	else
	{
		if (stat(cmd, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
			{
				error_is_dir(cmd);
			}
		}
	}
	return (1);
}
