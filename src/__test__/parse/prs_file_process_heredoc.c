/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file_process_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:54:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/17 05:11:08 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

char	*prs_make_heredoc_file(int count)
{
	char				*result;
	const char *const	tty = ttyname(STDIN_FILENO);
	char				**splited_strs;
	char				*tty_name;

	splited_strs = ft_split(tty, '/');
	tty_name = splited_strs[ft_strs_len((const char **)splited_strs) - 1];
	result = ft_strjoin(tty_name, "_");
	result = ft_strjoin_and_free(TK_HEREDOC_PATH, result, FREE_S2);
	ft_free_strs(splited_strs);
	return (ft_strjoin_and_free(result, ft_itoa(count), FREE_BOTH));
}

char	*prs_remove_quote_in_heredoc(t_prs_stack *stack)
{
	char	*result;

	result = NULL;
	printf("ori_str: %s\n", stack->ori_str);
	if (prs_is_double_quote(stack->ori_str++))
		result = ft_strndup(stack->ori_str, prs_count_str_using_func(stack->ori_str, prs_is_double_quote, FALSE));
	else
		result = ft_strndup(stack->ori_str, prs_count_str_using_func(stack->ori_str, prs_is_single_quote, FALSE));
	stack->ori_str += ft_strlen(result) + 1;
	printf("result: %s\n", result);
	return (result);
}

char	*prs_find_heredoc_limiter(t_prs_stack *stack, t_bool *flag)
{
	char	*limiter;
	char	*start;
	char	*tmp;

	limiter = ft_strdup("");
	start = stack->ori_str;
	stack->ori_str += prs_count_str_using_func(stack->ori_str, prs_is_redir, TRUE);
	stack->ori_str += prs_count_str_using_func(stack->ori_str, prs_is_white_space, TRUE);
	start = stack->ori_str;
	while (*stack->ori_str && !prs_is_white_space(stack->ori_str))
	{
		if (*stack->ori_str && prs_is_quote(stack->ori_str))
		{
			*flag = FALSE;
			tmp = ft_strndup(start, stack->ori_str - start);
			limiter = ft_strjoin_and_free(limiter, tmp, FREE_BOTH);
			tmp = prs_remove_quote_in_heredoc(stack);
			limiter = ft_strjoin_and_free(limiter, tmp, FREE_BOTH);
			start = stack->ori_str;
		}
		else
			stack->ori_str++;
	}
	if (start != stack->ori_str)
		limiter = ft_strjoin_and_free(limiter, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
	return (limiter);
}

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
