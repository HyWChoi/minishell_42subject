/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:11 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/01 17:43:44 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tksh.h"
#include <stdio.h>

void	env(const char **envp){
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
