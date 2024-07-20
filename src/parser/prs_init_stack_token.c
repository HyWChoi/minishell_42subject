/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_stack_token_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:41:44 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 16:41:45 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_token	**prs_init_token_list(size_t size, char ***envp)
{
	size_t	i;
	t_token	**token_list;

	token_list = NULL;
	i = 0;
	if (!ft_calloc_guard((void **)&token_list, size + 1, sizeof(t_token *)))
		return (NULL);
	while (i < size)
	{
		prs_init_token(token_list + i, envp);
		i++;
	}
	return (token_list);
}

void	prs_init_token(t_token **token, char	***envp)
{
	if (!ft_calloc_guard((void **)token, 1, sizeof(t_token)))
		return ;
	(*token)->envp = envp;
	(*token)->cmd_path = NULL;
	(*token)->argv = NULL;
	if (!ft_calloc_guard((void **)&((*token)->file),
			1, sizeof(t_file_list *)))
		return ;
}

static void	handle_stack_init(t_prs_stack **stack,
				char *start, char *len, char ***envp)
{
	char	*ori_str;

	ori_str = ft_strndup(start, len);
	prs_stack_init(stack, ori_str, envp);
	free(ori_str);
}

t_prs_stack	**prs_init_stack_list(char *ori_str, char ***envp)
{
	char		*start;
	int			i;
	int			count;
	t_prs_stack	**stack_lst;

	i = 0;
	count = 1 + prs_count_pipe(ori_str);
	start = ori_str;
	if (!ft_calloc_guard((void **)&stack_lst, count + 1, sizeof(t_prs_stack *)))
		return (NULL);
	while (*ori_str)
	{
		prs_skip_qoute(&ori_str);
		if (*ori_str == '|')
		{
			handle_stack_init(&stack_lst[i], start, ori_str - start, envp);
			start = ori_str + 1;
			i++;
		}
		ori_str++;
	}
	if (i < count)
		handle_stack_init(&stack_lst[i], start, ori_str - start, envp);
	return (stack_lst);
}

void	prs_stack_init(t_prs_stack	**stack, char *ori_str, char ***envp)
{
	size_t	size;

	if (!ft_calloc_guard((void **)stack, 1, sizeof(t_prs_stack)))
		return ;
	(*stack)->ori_str = ft_strtrim((const char *)ori_str, PRS_WHITE_SPACE);
	size = ft_strlen((const char *)(*stack)->ori_str);
	if (!ft_calloc_guard((void **)&((*stack)->stack), size + 1, sizeof(char *)))
		return ;
	if (!ft_calloc_guard(
			(void **)&((*stack)->argv_list), 1, sizeof(t_argv_list *)))
		return ;
	(*stack)->envp = envp;
	(*stack)->top = -1;
	(*stack)->size = size;
	(*stack)->is_double_quote = FALSE;
	(*stack)->is_single_quote = FALSE;
	(*stack)->var_flag = FALSE;
	(*stack)->err_flag = FALSE;
	if (!*(*stack)->ori_str)
		(*stack)->err_flag = TRUE;
}
