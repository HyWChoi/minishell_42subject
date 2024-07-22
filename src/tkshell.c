/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/22 17:41:45 by yechakim         ###   ########.fr       */
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
#include <stdlib.h>

sig_atomic_t	g_sig_flag = 0;

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

void	set_exit_code(t_exit_code exit_code, char ***envp)
{
	static char	***static_envp;

	if (envp)
		static_envp = envp;
	free(*static_envp[0]);
	**static_envp = ft_strjoin_and_free("?=", ft_itoa(exit_code), FREE_S2);
}

void	ex_unlink_heredoc_hook(t_token **token_list)
{
	t_file_list	*temp;

	while (*token_list)
	{
		temp = *(*token_list)->file;
		while (temp)
		{
			if (temp->type == HEREDOC)
				unlink(temp->file_name);
			temp = temp->next;
		}
		token_list++;
	}
}

static t_exit_code	missing_operand_check(t_token **token_list_ptr)
{
	t_token		**temp_token;
	t_file_list	*file_list;

	if (!token_list_ptr)
		return (throw_syntax_error());
	temp_token = token_list_ptr;
	while (*temp_token)
	{
		file_list = *(*temp_token)->file;
		while (file_list)
		{
			if (ft_strncmp(file_list->file_name, "", 1) == 0)
				return (throw_syntax_error());
			if (file_list->type == HEREDOC
				&& ft_strncmp(file_list->limiter, "", 1) == 0)
				return (throw_syntax_error());
			file_list = file_list->next;
		}
		temp_token++;
	}
	return (0);
}

int	main(int argc, char **argv, const char **initial_envp)
{
	t_token		**token_list;
	char		***envp;
	t_exit_code	exit_code;
	char		**tmp;
	char		*origin_str;

	(void)argc;
	(void)argv;
	token_list = NULL;
	tmp = copy_envp(initial_envp);
	envp = &tmp;
	set_exit_code(0, envp);
	while (1)
	{
		origin_str = tksh_prompt(**envp);
		if (!origin_str)
			continue ;
		token_list = prs_parse(origin_str, envp);
		exit_code = missing_operand_check(token_list);
		if (exit_code != 0)
		{
			set_exit_code(exit_code, envp);
			continue ;
		}
		exit_code = execute(token_list);
		if (token_list)
			ex_unlink_heredoc_hook(token_list);
		set_exit_code(exit_code, envp);
		if (token_list)
			tksh_free_token_list(token_list);
	}
	return (0);
}
