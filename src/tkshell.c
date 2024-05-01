/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:40:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/01 16:07:00 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include <stdio.h>

int main(int argc, char **argv, const char **initial_envp)
{
	char	*envp;

	(void)argc;
	(void)argv;
	envp = ft_strdup(*initial_envp);
	while (1)
	{
		char *tokens = tksh_prompt(envp);
		printf("tokens: %s\n", tokens);
		// while(token)
		// {
		// 	// if (is_builtin(tocken))
		// 	// 	// run_builtin(token);
		// 	// else
		// 	// 	run_executable(token);
			
		// }
		// 시그널에 따른 종료
		
	}
	return (0);
}


