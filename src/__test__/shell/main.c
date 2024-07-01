/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/01 21:27:30 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include "tksh_parse.h"

/**
 * @brief main of test
 * IMPORTANT: This is a MAIN Function of "test_shell"
*/
int main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	(void)argc;
	(void)argv;

	token_list = NULL;
	char **tmp = ft_strs_copy(initial_envp);
	envp = &tmp;
	while (1)
	{
		char *origin_str = tksh_prompt(**envp);
		printf("origin str: %s\n", origin_str);
		token_list = prs_parse(origin_str, envp);
		dbg_print_token(token_list);
		if(*token_list)
			builtin_handler(token_list[0]);
		if (token_list)
		{
			tksh_free_token_list(token_list);
		}
	}
	return (0);
}
