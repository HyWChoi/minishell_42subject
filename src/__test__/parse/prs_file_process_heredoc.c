/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file_process_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:54:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/16 20:52:16 by hyeonwch         ###   ########.fr       */
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

char	*prs_remove_quote_in_heredoc(t_prs_stack *stack, t_bool (*f)(char *))
{
	char	*result;

	result = NULL;
	if (f(stack->ori_str))
	{
		stack->ori_str++;
		result = ft_strndup(stack->ori_str, prs_count_str_using_func(stack->ori_str, f, TRUE));
		stack->ori_str += ft_strlen(result) + 1;
	}
	else
	{
		stack->ori_str++;
		result = ft_strndup(stack->ori_str, prs_count_str_using_func(stack->ori_str, f, TRUE));
		stack->ori_str += ft_strlen(result) + 1;
	}
	return (result);
}

char	*prs_find_limiter(t_prs_stack *stack)
{
	char	*result;
	char	*tmp;
	char	*start;

	tmp = NULL;
	start = stack->ori_str;
	result = ft_strdup("");
	stack->ori_str += prs_count_str_using_func(stack->ori_str, prs_is_white_space, TRUE);
	if (!*stack->ori_str)
	{
		stack->err_flag = TRUE;
		return (NULL);
	}
	while (*stack->ori_str && !prs_is_white_space(stack->ori_str))
	{
		if (prs_is_quote(stack->ori_str))
		{
			result = ft_strjoin_and_free(result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
			tmp = prs_remove_quote_in_heredoc(stack, prs_is_quote);
			result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
			start = stack->ori_str;
		}
		else
			stack->ori_str++;
	}
	if (stack->ori_str != start)
		result = ft_strjoin_and_free(result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
	return (result);
}

void	prs_set_heredoc_file(t_token *token, t_prs_stack *stack,
			t_file_type type)
{
	char	*limiter;

	limiter = prs_find_file_name(stack);
	prs_file_list_add_node(
		prs_create_file_list(NULL, type, limiter), token->file);
}
