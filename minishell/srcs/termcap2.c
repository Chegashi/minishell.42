/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:27:44 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/08 16:41:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	ft_enter_line(t_shell *shell)
{
	shell->enter = 0;
	ft_putstr("\n");
	if (*(shell->line) != 0)
	{
		add_to_history(shell);
		shell->hist_last = ft_histlast(shell->hist);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->orig_term);
}

void	ft_ctrld(t_shell *shell)
{
	if (shell->line && ft_strlen(shell->line) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}

void	add_to_history(t_shell *shell)
{
	t_hist	*prev_node;
	t_hist	*new_node;

	if (ft_histsize(shell->hist) == 1)
	{
		ft_histadd_front(&shell->hist, ft_histnew(ft_strdup(shell->line)));
		ft_histlast(shell->hist)->prev = shell->hist;
	}
	else if (ft_histsize(shell->hist))
	{
		new_node = ft_histnew(ft_strdup(shell->line));
		prev_node = ft_histlast(shell->hist)->prev;
		new_node->next = prev_node->next;
		prev_node->next = new_node;
		new_node->prev = prev_node;
		if (new_node->next != NULL)
			new_node->next->prev = new_node;
	}
}
