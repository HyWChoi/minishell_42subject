/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_make_argv_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:37:56 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/20 16:37:58 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

char	*prs_make_argv_str(t_prs_stack *stack)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	while (prs_is_end_of_name(stack->ori_str + i))
		i++;
	result = ft_strndup((const char *)stack->ori_str, i);
	if (ft_strchr(result, '$'))
	{
		temp = result;
		result = prs_parse_variable(result, stack->envp);
		if (!*result)
		{
			free(temp);
			stack->ori_str += i;
			stack->var_flag = TRUE;
			return (result);
		}
		prs_extract_var_by_split(&result, stack);
		stack->var_flag = TRUE;
		free(temp);
	}
	stack->ori_str += i;
	return (result);
}

char	*prs_extract_var_by_split(char **result, t_prs_stack *stack)
{
	char	**splited_str;
	size_t	j;
	size_t	len;

	j = 0;
	splited_str = ft_split(*result, ' ');
	len = ft_strs_len((const char **)splited_str);
	while (j < len - 1)
		if (splited_str[j])
			prs_argv_list_add_node(ft_strdup(splited_str[j++]), stack);
	free(*result);
	*result = ft_strdup(splited_str[j]);
	ft_free_strs(splited_str);
	return (*result);
}

void	prs_finalize_result(char *result,
		t_prs_stack *stack)
{
	if (!(*result))
		free(result);
	else
	{
		prs_argv_list_add_node(result, stack);
		free(result);
	}
}

char	*prs_handle_whitespace(t_prs_stack *stack, char *tmp, char *result)
{
	if (prs_is_white_space(stack->ori_str))
	{
		stack->ori_str++;
		if (tmp)
		{
			result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
			prs_argv_list_add_node(result, stack);
			result = ft_strdup("");
		}
	}
	else
		result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
	if (!*stack->ori_str)
	{
		prs_argv_list_add_node(result, stack);
		result = ft_strdup("");
	}
	return (result);
}
