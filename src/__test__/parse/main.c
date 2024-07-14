/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 13:52:54 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include <stdio.h>
#include <stdlib.h>

void	leaks(void)
{
	system("leaks prs_test");
}

int	main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	char	**tmp;
	char	*origin_str;

	(void)argc;
	(void)argv;
	token_list = NULL;
	tmp = ft_strs_copy(initial_envp);
	envp = &tmp;
	origin_str = NULL;
	while (1)
	{
		leaks();
		origin_str = tksh_prompt(**envp);
		token_list = prs_parse(origin_str, envp);
		dbg_print_token(token_list);
		if (token_list)
			tksh_free_token_list(token_list);
	}
	return (0);
}
