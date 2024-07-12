#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

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
		result = ft_strjoin_and_free(result,
				ft_strndup(*start, stack->ori_str - *start), FREE_BOTH);
		temp = prs_remove_quote(stack);
		result = ft_strjoin_and_free(result, temp, FREE_BOTH);
		*start = stack->ori_str;
	}
	else if (prs_is_variable(stack->ori_str))
	{
		result = ft_strjoin_and_free(result,
				ft_strndup(*start, stack->ori_str - *start), FREE_BOTH);
		temp = prs_parse_variable(stack->ori_str, stack->envp);
		if (temp)
			result = ft_strjoin_and_free(result, temp, FREE_BOTH);
		stack->ori_str += prs_count_str_using_func(
				stack->ori_str, prs_is_end_of_name, TRUE);
		*start = stack->ori_str;
	}
	return (result);
}

char	*prs_finalize_result(t_prs_stack *stack, char *result, char *start)
{
	if (stack->ori_str != start)
		result = ft_strjoin_and_free(
				result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
	stack->ori_str += prs_count_str_using_func(
			stack->ori_str, prs_is_white_space, TRUE);
	if (*result && (
			ft_strncmp(result, "<", ft_strlen(result)) == 0
			|| ft_strncmp(result, ">", ft_strlen(result)) == 0
			|| ft_strncmp(result, ">>", ft_strlen(result)) == 0
			|| ft_strncmp(result, "<<", ft_strlen(result)) == 0))
		stack->err_flag = TRUE;
	return (result);
}

char	*prs_find_file_name(t_prs_stack *stack)
{
	size_t	i;
	char	*start;
	char	*result;

	result = ft_strdup("");
	i = prs_skip_redir_and_whitespace(stack);
	start = stack->ori_str;
	while (!stack->err_flag
		&& *stack->ori_str
		&& !prs_is_white_space(stack->ori_str))
	{
		result = prs_process_quote_or_variable(stack, result, &start);
		if (!prs_is_quote(stack->ori_str) && !prs_is_variable(stack->ori_str))
			stack->ori_str++;
	}
	result = prs_finalize_result(stack, result, start);
	return (result);
}
