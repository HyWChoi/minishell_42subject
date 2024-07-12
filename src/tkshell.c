/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/12 16:24:09 by hyeonwch         ###   ########.fr       */
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

sig_atomic_t g_sig_flag=0;
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
	new_envp[i] = ft_strdup("?=0");
	i++;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i + 1] = NULL;
	return (new_envp);
}



static void set_exit_code(t_exit_code exit_code, char ***envp)
{
	free(*envp[0]);
	**envp = ft_strjoin_and_free("?=", ft_itoa(exit_code), FREE_S2);
}


void ex_unlike_heredoc_hook(t_token **token_list)
{
	t_file_list *temp;

	while (*token_list)
	{
		temp = *(*token_list)->file;
		while(temp)
		{
			if (temp->type == HEREDOC)
				unlink(temp->file_name);
			temp = temp->next;
		}
		token_list++;
	}
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
		// leak_check();
		g_sig_flag = SIGINT_FLAG_OFF;
		char *origin_str = tksh_prompt(**envp);
		if (ft_strlen(origin_str) == 0)
		{
			if (g_sig_flag == SIGINT_FLAG_ON)
				set_exit_code(1, envp);
			continue;
		}
		token_list = prs_parse(origin_str, envp);
		// dbg_print_token(token_list);
		exit_code = execute(token_list);
		ex_unlike_heredoc_hook(token_list);
		set_exit_code(exit_code, envp);
		if (token_list)
			tksh_free_token_list(token_list);
		// rl_on_new_line();
	}
	return (0);
}
