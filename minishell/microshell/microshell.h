/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:34:39 by mochegri          #+#    #+#             */
/*   Updated: 2021/07/02 08:57:01 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_v_env
{
    char                *key;
    char                *value;
    struct s_v_env      *next;
}       t_v_env;
t_v_env *str_to_v_env(char *str);
int     ft_strlen_dil(char *str, char d, char d2);
t_v_env *init_envp(char **envp);
void    __env__(t_v_env *head);
char    *get_value(char *key, t_v_env *head);
void    __unset(char *key, t_v_env **head);
void	echo(char *str, t_v_env *head);
char	*key_from_str(char *str);
char	*value_from_str(char *str);


int		ft_atoi(char *s);
int		ft_isdigit(int c);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
void	ft_exit(void);
char	**ft_split(char *s, char c);
void	ft_putnbr(int nb);
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int     ft_strcmp(char *s1, char *s2);
void	ft_putchar(char c);