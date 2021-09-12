/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:53:07 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/07/28 13:24:24 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(char *str1, char *str2);
int		ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isprint(int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isprint(int c);
int		ft_atoi(const char *str);
char	*ft_strchr(char *s, int c);
int		ft_isdigit(int c);
char	*ft_strstr(char *str, char *to_find);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_itoa(int n);
#endif
