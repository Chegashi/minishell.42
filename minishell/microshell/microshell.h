/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:34:39 by mochegri          #+#    #+#             */
/*   Updated: 2021/06/30 19:54:06 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_var
{
    char            *key;
    char            *value;
    struct s_var    *next;
}              t_var;

t_var     *init_envp(char **env);
void	ft_fill_var(t_var **var, char *str);
char    *ft_get_key(char *str);
char	*ft_get_value(char *str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);