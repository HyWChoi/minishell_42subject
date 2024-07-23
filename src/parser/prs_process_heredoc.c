/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:39:52 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 12:01:08 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	prs_set_heredoc_file(t_token *token, t_prs_stack *stack,
			t_file_type type)
{
	char	*limiter;
	t_bool	flag;

	flag = TRUE;
	limiter = prs_find_heredoc_limiter(stack, &flag);
	if (!*limiter)
	{
		stack->err_flag = TRUE;
		free(limiter);
		return ;
	}
	prs_file_list_add_node(
		prs_create_file_list(NULL, type, limiter, flag), token->file);
}

char	*prs_make_heredoc_file(int count)
{
	char				*result;
	const char *const	tty = ttyname(STDIN_FILENO);
	char				**splited_strs;
	char				*tty_name;

	splited_strs = ft_split(tty, '/');
	tty_name = splited_strs[ft_strs_len((const char **)splited_strs) - 1];
	result = ft_strjoin(tty_name, "_");
	result = prs_safety_strjoin_and_free(TK_HEREDOC_PATH, result, FREE_S2);
	ft_free_strs(splited_strs);
	return (prs_safety_strjoin_and_free(result, ft_itoa(count), FREE_BOTH));
}

char	*prs_remove_quote_in_heredoc(t_prs_stack *stack)
{
	char	*result;

	result = NULL;
	if (prs_is_double_quote(stack->ori_str++))
		result = prs_safety_strndup(stack->ori_str, prs_count_str_using_func
				(stack->ori_str, prs_is_double_quote, FALSE));
	else
		result = prs_safety_strndup(stack->ori_str, prs_count_str_using_func
				(stack->ori_str, prs_is_single_quote, FALSE));
	stack->ori_str += ft_strlen(result) + 1;
	printf("result: %s\n", result);
	return (result);
}

void	prs_skip_for_heredoc_limiter(t_prs_stack *stack, char **start)
{
	stack->ori_str += prs_count_str_using_func(stack->ori_str,
			prs_is_redir, TRUE);
	stack->ori_str += prs_count_str_using_func(stack->ori_str,
			prs_is_white_space, TRUE);
	*start = stack->ori_str;
}

char	*prs_find_heredoc_limiter(t_prs_stack *stack, t_bool *flag)
{
	char	*limiter;
	char	*start;
	char	*tmp;

	limiter = prs_safety_strdup("");
	start = stack->ori_str;
	prs_skip_for_heredoc_limiter(stack, &start);
	while (*stack->ori_str && !prs_is_white_space(stack->ori_str))
	{
		if (*stack->ori_str && prs_is_quote(stack->ori_str))
		{
			*flag = FALSE;
			tmp = prs_safety_strndup(start, stack->ori_str - start);
			limiter = prs_safety_strjoin_and_free(limiter, tmp, FREE_BOTH);
			tmp = prs_remove_quote_in_heredoc(stack);
			limiter = prs_safety_strjoin_and_free(limiter, tmp, FREE_BOTH);
			start = stack->ori_str;
		}
		else
			stack->ori_str++;
	}
	if (start != stack->ori_str)
		limiter = prs_safety_strjoin_and_free(limiter,
				prs_safety_strndup(start, stack->ori_str - start), FREE_BOTH);
	return (limiter);
}
