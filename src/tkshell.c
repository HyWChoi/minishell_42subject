/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 16:30:13 by hyeonwch         ###   ########.fr       */
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

static void	set_exit_code(t_exit_code exit_code, char ***envp)
{
	free(*envp[0]);
	**envp = ft_strjoin_and_free("?=", ft_itoa(exit_code), FREE_S2);
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

static t_exit_code missing_operand_check(t_token ***token_list_ptr)
{
	t_token 	**token_list;
	t_file_list *file_list;

	if(!*token_list_ptr)
	{
		ft_putstr_fd("tksh: Syntax Error precheck\n", 2);
		return (2);
	}
	token_list = *token_list_ptr;
	while (*token_list)
	{
		file_list = *(*token_list)->file;
		while(file_list)
		{
			if (ft_strncmp(file_list->file_name, "", 1) == 0)
			{
				ft_putstr_fd("tksh: Syntax Error\n", 2);
				return (2);
			}
			if(file_list->type == HEREDOC && ft_strncmp(file_list->limiter, "", 1) == 0)
			{
				ft_putstr_fd("tksh: Syntax Error\n", 2);
				return (2);
			}
			file_list = file_list->next;
		}
		token_list++;
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
	exit_code = 0;
	// set_exit_code(0);
	while (1)
	{
		g_sig_flag = SIGINT_FLAG_OFF;
		origin_str = tksh_prompt(**envp);
		if(!origin_str)
			continue ;
		if (ft_strlen(origin_str) == 0)
		{
			if (g_sig_flag == SIGINT_FLAG_ON)
				set_exit_code(1, envp);
			continue ;
		}
		token_list = prs_parse(origin_str, envp);
		dbg_print_token(token_list);
		exit_code = missing_operand_check(&token_list);
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
