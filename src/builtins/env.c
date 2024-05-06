/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:11 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/06 14:28:53 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <stdio.h>

void	env(const char **envp){
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
