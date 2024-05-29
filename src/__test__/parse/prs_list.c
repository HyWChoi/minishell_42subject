#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	prs_add_argv_in_token(char *str, t_argv_list	**head)
{
	t_argv_list	*last;

	if (!*head)
		*head = prs_new_token_arg(str);
	else
	{
		last = prs_find_last_argv_list(head);
		last->next = prs_new_token_arg(str);
	}
}

void	prs_add_file_in_token(t_token *token, t_prs_stack *stack)
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

char	*prs_make_argv(t_prs_stack *stack, char ***envp)
{
	int	i;
	char	*result;

	i = 0;
	while (*(stack->ori_str + i) && !prs_is_white_space(stack->ori_str + i) && !prs_is_redir(stack->ori_str + i) && !prs_is_quote(stack->ori_str + i))
		i++;
	result = ft_strndup((const char *)stack->ori_str, i - 1);
	if (ft_strchr(result, '$'))
		result = prs_find_envp(result, envp);
	stack->ori_str += i;
	return (result);
}

size_t	prs_count_list(t_argv_list **start)
{
	size_t	i;
	t_argv_list	*tmp;

	i = 0;
	tmp = *start;
	if (start == NULL || *start == NULL)
		return (i);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	printf("list count: %zu\n", i);
	return (i);
}

void	prs_set_argv_in_token(t_token *token, t_argv_list **argv_list, t_prs_stack *stack)
{
	size_t	list_size;
	size_t	i;
	t_argv_list	*tmp;

	i = 0;
	list_size = prs_count_list(argv_list);
	tmp = *argv_list;
	if (stack->err_flag || list_size == 0)
		return (prs_free_arg_list(argv_list));
	if(!ft_calloc_guard((void **)&(token->argv), list_size + 1, sizeof(char **)))
		return ;
	while (tmp)
	{
		*(token->argv + i) = ft_strdup(prs_get_str_argv(tmp));
		tmp = tmp->next;
		i++;
	}
	prs_free_arg_list(argv_list);
}
