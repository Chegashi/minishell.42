/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:19:12 by mochegri          #+#    #+#             */
/*   Updated: 2021/06/30 20:03:43 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int main(int ac, char **av, char **envp)
{
    t_var   *env;

    env = init_envp(envp);
    while(env)
    {
        printf("%s\t=\t%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}