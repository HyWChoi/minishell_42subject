/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_arg_list_set_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:50:57 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:02:25 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

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

void	prs_set_argv_into_token(
			t_token *token, t_prs_stack *stack)
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
