/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:08:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/15 12:41:29 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	*prs_set_token(t_prs_stack *stack, t_token *token)
{
	t_argv_list	*argv_list;
	char		*start;
	char		*result;

	argv_list = NULL;
	result = ft_strdup("");
	start = stack->ori_str;
	while (!stack->err_flag && *stack->ori_str)
		result = prs_process_stack(stack, token, result, &argv_list);
	finalize_result(result, &argv_list, stack);
	prs_set_argv_into_token(token, &argv_list, stack);
	stack->ori_str = start;
	return (token);
}

void	set_heredoc_path(t_token **token)
{
	t_file_list	*file_list;
	int			count;

	count = 0;
	while (token && *token)
	{
		file_list = *(*token)->file;
		while (file_list)
		{
			if (file_list->type == HEREDOC)
			{
				file_list->file_name = prs_make_heredoc_file(count);
				count++;
			}
			file_list = file_list->next;
		}
		token++;
	}
}

void	*prs_err_free_all(char *usr_input,
		t_prs_stack **stack_list, t_token **token_list)
{
	free(usr_input);
	prs_free_stack_list(stack_list);
	tksh_free_token_list(token_list);
	return (NULL);
}

static void	prs_init_stack_token_lists(t_prs_stack ***stack_list,
		t_token ***token_list, char *usr_input, char ***envp)
{
	char	*trimed_input;

	trimed_input = ft_strtrim(usr_input, PRS_WHITE_SPACE);
	if (*trimed_input == '\0' || *trimed_input == '|'
		|| *(trimed_input + ft_strlen(trimed_input) - 1) == '|')
	{
		free(trimed_input);
		*stack_list = NULL;
		*token_list = NULL;
		return ;
	}
	*stack_list = prs_init_stack_list(trimed_input, envp);
	*token_list = prs_init_token_list(ft_strs_len((const char **)*stack_list),
			envp);
	free(trimed_input);
}

t_token	**prs_parse(char *usr_input, char ***envp)
{
	t_prs_stack	**stack_list;
	t_token		**token_list;
	int			i;

	i = 0;
	if (!prs_is_balanced_quote(usr_input))
		return (handle_unbalanced_quote(usr_input));
	prs_init_stack_token_lists(&stack_list, &token_list, usr_input, envp);
	while (stack_list && stack_list[i])
	{
		if (!prs_set_token(stack_list[i], token_list[i]))
			return (prs_err_free_all(usr_input, stack_list, token_list));
		prs_set_cmd_path_in_token(token_list[i]);
		if (is_check_err_in_stack(stack_list[i]))
		{
			tksh_free_token_list(token_list);
			token_list = NULL;
			break ;
		}
		i++;
	}
	prs_free_stack_list(stack_list);
	set_heredoc_path(token_list);
	free(usr_input);
	return (token_list);
}
