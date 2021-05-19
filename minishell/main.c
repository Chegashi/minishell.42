/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:28:45 by mochegri          #+#    #+#             */
/*   Updated: 2021/05/19 16:57:35 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main(int ac, char **av, char *envp[])
{
	while (*envp)
		printf("%s\n", *(envp++));
	*envp++ = strdup("walo=nuhljhr");
	*envp++ = strdup("wa88888lo=nuhlj555555hr");
	return(0);
}