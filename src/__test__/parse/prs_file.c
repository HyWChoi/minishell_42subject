#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief prs_set_file_path_in_token
 *
 * This function sets the file path in the given token based on the stack's original string.
 * It determines if the file path is for input or output, checks for heredoc, and updates the token accordingly.
 *
 * @param t_token* token - The token to update with the file path.
 * @param t_prs_stack* stack - The stack containing the original string and error flag.
 */
void	prs_set_file_path_in_token(t_token *token, t_prs_stack *stack)
{
	t_file_type type;

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

/**
 * @brief prs_find_file_name
 *
 * This function finds the file name in the stack's original string.
 * It skips redirection characters and white spaces, removes quotes if present, and extracts the file name.
 *
 * @param t_prs_stack* stack - The stack containing the original string and error flag.
 * @return char* - The extracted file name, or NULL if an error occurs.
 */
char	*prs_find_file_name(t_prs_stack *stack)
{
	size_t	i;
	char	*start;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	temp = NULL;
	i = prs_count_str_using_func(stack->ori_str, prs_is_redir, TRUE);
	stack->ori_str += i;
	i = prs_count_str_using_func(stack->ori_str, prs_is_white_space, TRUE);
	stack->ori_str += i;
	start = stack->ori_str;
	while (!stack->err_flag && *stack->ori_str && !prs_is_white_space(stack->ori_str))
	{
		printf("stack->ori_str:%s\n", stack->ori_str);
		if (prs_is_quote(stack->ori_str))
		{
			result = ft_strjoin_and_free(result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
			temp = prs_remove_quote(stack);
			result = ft_strjoin_and_free(result, temp, FREE_BOTH);
			start = stack->ori_str;
		}
		else if (prs_is_variable(stack->ori_str))
		{
			result = ft_strjoin_and_free(result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
			temp = prs_parse_variable(stack->ori_str, stack->envp);
			if (temp)
				result = ft_strjoin_and_free(result, temp, FREE_BOTH);
			stack->ori_str += prs_count_str_using_func(stack->ori_str, prs_is_end_of_name, TRUE);
			start = stack->ori_str;
		}
		else
			stack->ori_str++;
	}
	if (stack->ori_str != start)
		result = ft_strjoin_and_free(result, ft_strndup(start, stack->ori_str - start), FREE_BOTH);
	stack->ori_str += prs_count_str_using_func(stack->ori_str, prs_is_white_space, TRUE);
	if (*result &&
			(ft_strncmp(result, "<", ft_strlen((const char *)result)) == 0
			 || ft_strncmp(result, ">", ft_strlen((const char *)result)) == 0
			 || ft_strncmp(result, ">>", ft_strlen((const char *)result)) == 0
			 || ft_strncmp(result, "<<", ft_strlen((const char *)result)) == 0))
		stack->err_flag = TRUE;
	if (!*result)
	{
		result = NULL;
	}
	return (result);
}
