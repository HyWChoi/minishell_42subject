/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_set_in_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:52:41 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 01:12:16 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	*prs_set_token(t_prs_stack *stack, t_token *token)
{
	char		*start;
	char		*result;

	result = ft_strdup("");
	start = stack->ori_str;
	while (!stack->err_flag && *stack->ori_str)
		result = prs_process_stack(stack, token, result);
	prs_finalize_result(result, stack);
	prs_set_argv_into_token(token, stack);
	stack->ori_str = start;
	return (token);
}

void	prs_set_cmd_path_in_token(t_token *token)
{
	if (token->argv && token->argv[0])
		token->cmd_path = ft_strdup(token->argv[0]);
}

void	prs_set_argv_into_token(t_token *token, t_prs_stack *stack)
{
	size_t		list_size;
	size_t		i;
	t_argv_list	*tmp;
	t_argv_list	**argv_list;

	argv_list = stack->argv_list;
	i = 0;
	list_size = prs_argv_list_count(argv_list);
	tmp = *argv_list;
	if (stack->err_flag || list_size == 0)
		return (prs_free_arg_list(argv_list));
	if (!ft_calloc_guard(
			(void **)&(token->argv), list_size + 1, sizeof(char **)))
		return ;
	while (tmp)
	{
		*(token->argv + i) = ft_strdup(prs_argv_list_get_str(tmp));
		tmp = tmp->next;
		i++;
	}
	prs_free_arg_list(argv_list);
}

void	prs_set_file_path_in_token(t_token *token, t_prs_stack *stack)
{
	t_file_type	type;

	if (!stack->ori_str || stack->err_flag)
		return ;
	if (prs_is_in_file(stack->ori_str))
	{
		type = IN_FILE;
		prs_setting_file(token, stack, prs_is_in_file, type);
	}
	else if (prs_is_out_file(stack->ori_str))
	{
		type = OUT_FILE;
		prs_setting_file(token, stack, prs_is_out_file, type);
	}
}

void	prs_set_heredoc_path(t_token **token)
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
