/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:11 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/12 16:24:09 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <stdio.h>

t_exit_code	env(const char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL && *envp[i] != '?') //TODO: exitcode 숨기기
			printf("%s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
