/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/09 18:46:30 by hyeonwch         ###   ########.fr       */
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

static char	**copy_envp(const char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	if (!ft_calloc_guard((void **)&new_envp, i + 2, sizeof(char *)))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup("?=0");
	new_envp[i + 1] = NULL;
	return (new_envp);
}

int main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	t_exit_code exit_code = 0;
	(void)argc;
	(void)argv;

	token_list = NULL;
	char **tmp = copy_envp(initial_envp);
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
