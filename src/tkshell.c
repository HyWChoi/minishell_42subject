/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/09 11:34:32 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include "tksh_execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

int main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	t_exit_code exit_code = 0;
	(void)argc;
	(void)argv;

	token_list = NULL;
	char **tmp = ft_strs_copy(initial_envp);
	envp = &tmp;
	// set_exit_code(0);
	while (1)
	{
		char *origin_str = tksh_prompt(**envp);
		token_list = prs_parse(origin_str, envp);
		// dbg_print_token(token_list);
		exit_code = execute(token_list);
		if (token_list)
		{
			tksh_free_token_list(token_list);
		}
		// rl_on_new_line();
	}
	return (0);
}
