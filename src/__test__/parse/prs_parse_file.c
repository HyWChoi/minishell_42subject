#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_check_redir_valid(char *str, t_token *token)
{
	if (prs_is_in_file(str))
	{
		if (prs_is_in_file(str + 1))
			token->is_heredoc = TRUE;
	}
	else if (prs_is_out_file(str))
	{
		if (prs_is_out_file(str + 1))
			token->is_append = TRUE;
	}
	return (TRUE);
}

char	*prs_find_file_name(t_prs_stack *stack)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	while (*(stack->ori_str + i) && prs_is_redir(stack->ori_str))
		stack->ori_str++;
	while (*(stack->ori_str + i) && prs_is_white_space(stack->ori_str) )
		stack->ori_str++;
	if (*(stack->ori_str + i) && prs_is_quote(stack->ori_str))
		return (prs_remove_quote(stack));
	else if (*(stack->ori_str + i) && prs_is_redir(stack->ori_str))
		stack->err_flag = TRUE;
	while (!stack->err_flag && *(stack->ori_str + i) && !prs_is_white_space(stack->ori_str + i) && !prs_is_redir(stack->ori_str + i) && !prs_is_quote(stack->ori_str))
		i++;
	if (i > 0 && !stack->err_flag)
		result = ft_strndup(stack->ori_str, i - 1);
	stack->ori_str += i;
	return (result);
}
