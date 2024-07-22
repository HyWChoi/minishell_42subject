/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:46:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 06:13:09 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	prs_setting_file(
	t_token *token, t_prs_stack *stack,
	t_bool (*judge_file_type)(char *str), t_file_type type)
{
	char	*file_name;

	file_name = NULL;
	prs_redir_err(stack);
	if (judge_file_type(stack->ori_str + 1))
	{
		if (type == OUT_FILE)
			type = APPEND;
		else
		{
			type = HEREDOC;
			prs_set_heredoc_file(token, stack, type);
			return ;
		}
	}
	else
		if (prs_is_redir(stack->ori_str + 1))
			stack->err_flag = TRUE;
	file_name = prs_find_file_name(stack);
	if (!*file_name)
	{
		free(file_name);
		stack->err_flag = TRUE;
	}
	prs_file_check_and_add_node(file_name, stack, token, type);
}

size_t	prs_skip_redir_and_whitespace(t_prs_stack *stack)
{
	size_t	i;

	i = prs_count_str_using_func(stack->ori_str, prs_is_redir, TRUE);
	stack->ori_str += i;
	i = prs_count_str_using_func(stack->ori_str, prs_is_white_space, TRUE);
	stack->ori_str += i;
	return (i);
}

char	*prs_process_quote_or_variable(
	t_prs_stack *stack, char *result, char **start)
{
	char	*temp;

	if (prs_is_quote(stack->ori_str))
	{
		result = prs_safety_strjoin_and_free(result,
				prs_safety_strndup(*start, stack->ori_str - *start), FREE_BOTH);
		temp = prs_remove_quote(stack);
		result = prs_safety_strjoin_and_free(result, temp, FREE_BOTH);
		*start = stack->ori_str;
	}
	else if (prs_is_variable(stack->ori_str))
	{
		result = prs_safety_strjoin_and_free(result,
				prs_safety_strndup(*start, stack->ori_str - *start), FREE_BOTH);
		temp = prs_parse_variable(stack->ori_str, stack->envp);
		if (temp)
			result = prs_safety_strjoin_and_free(result, temp, FREE_BOTH);
		stack->ori_str += prs_count_str_using_func(
				stack->ori_str, prs_is_end_of_name, TRUE);
		*start = stack->ori_str;
	}
	return (result);
}

char	*prs_find_file_name(t_prs_stack *stack)
{
	char	*start;
	char	*result;

	result = prs_safety_strdup("");
	prs_skip_redir_and_whitespace(stack);
	start = stack->ori_str;
	while (!stack->err_flag
		&& *stack->ori_str
		&& !prs_is_white_space(stack->ori_str)
		&& !prs_is_redir(stack->ori_str))
	{
		result = prs_process_quote_or_variable(stack, result, &start);
		if (prs_is_quote(stack->ori_str) || prs_is_variable(stack->ori_str))
			continue ;
		if (*stack->ori_str
			&& !prs_is_white_space(stack->ori_str)
			&& !prs_is_redir(stack->ori_str))
			stack->ori_str++;
	}
	result = prs_finalize_file_result(stack, result, start);
	return (result);
}

char	*prs_finalize_file_result(t_prs_stack *stack, char *result, char *start)
{
	if (stack->ori_str != start)
		result = prs_safety_strjoin_and_free(
				result, prs_safety_strndup(start,
					stack->ori_str - start), FREE_BOTH);
	stack->ori_str += prs_count_str_using_func(
			stack->ori_str, prs_is_white_space, TRUE);
	if (*result && (*result == '<' || *result == '>' || *result == '|'))
	{
		free(result);
		stack->err_flag = TRUE;
		return (NULL);
	}
	return (result);
}
