/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/06 15:05:18 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include <stdio.h>

/**
 * @brief main of test
 * IMPORTANT: This is a MAIN Function of "test_shell"
*/
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
	}
	return (0);
}
