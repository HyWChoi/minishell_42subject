#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	prs_set_file_path_in_token(t_token *token, t_prs_stack *stack)
{
	if (prs_is_in_file(stack->ori_str))
	{
		if (prs_is_in_file(stack->ori_str + 1))
			token->is_heredoc = TRUE;
		token->infile_path = prs_find_file_name(stack);
		if (!token->infile_path)
			stack->err_flag = TRUE;
	}
	else if (prs_is_out_file(stack->ori_str))
	{
		if (prs_is_out_file(stack->ori_str + 1))
			token->is_heredoc = TRUE;
		token->outfile_path = prs_find_file_name(stack);
		if (!token->outfile_path)
			stack->err_flag = TRUE;
	}
}

char	*prs_find_file_name(t_prs_stack *stack)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	while (*stack->ori_str && prs_is_redir(stack->ori_str))
		stack->ori_str++;
	while (*stack->ori_str && prs_is_white_space(stack->ori_str) )
		stack->ori_str++;
	if (*stack->ori_str && prs_is_quote(stack->ori_str))
		return (prs_remove_quote(stack, stack->envp));
	else if (*stack->ori_str && prs_is_redir(stack->ori_str))
		stack->err_flag = TRUE;
	while (!stack->err_flag && prs_is_end_of_name(stack->ori_str + i))
		i++;
	if (i > 0 && !stack->err_flag)
		result = ft_strndup(stack->ori_str, i);
	stack->ori_str += i;
	return (result);
}

// t_bool	prs_check_redir_valid(char *str, t_token *token)
// {
// 	if (prs_is_in_file(str))
// 	{
// 		if (prs_is_in_file(str + 1))
// 			token->is_heredoc = TRUE;
// 	}
// 	else if (prs_is_out_file(str))
// 	{
// 		if (prs_is_out_file(str + 1))
// 			token->is_append = TRUE;
// 	}
// 	return (TRUE);
// }
