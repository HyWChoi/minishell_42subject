#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief prs_make_argv_str
 *
 * This function will make the argv string
 * stack->ori_str will be updated
 * stack->ori_str should be not qouted string
 *
 * @param t_prs_stack* stack
 * @return char*
*/
char	*prs_make_argv_str(t_prs_stack *stack)
{
	int	i;
	char	*result;

	i = 0;
	while (prs_is_end_of_name(stack->ori_str + i))
		i++;
	result = ft_strndup((const char *)stack->ori_str, i);
	stack->ori_str += i;
	return (result);
}

/**
 * @brief prs_set_argv_into_token
 *
 * This function will set the argv into token
 * stack->ori_str will be updated
 * stack->ori_str should be not qouted string
 *
 * @param t_token* token
 * @param t_argv_list** argv_list
 * @param t_prs_stack* stack
*/
void	prs_set_argv_into_token(t_token *token, t_argv_list **argv_list, t_prs_stack *stack)
{
	size_t	list_size;
	size_t	i;
	t_argv_list	*tmp;

	i = 0;
	list_size = prs_argv_list_count(argv_list);
	tmp = *argv_list;
	if (stack->err_flag || list_size == 0)
		return (prs_free_arg_list(argv_list));
	if(!ft_calloc_guard((void **)&(token->argv), list_size + 1, sizeof(char **)))
		return ;
	while (tmp)
	{
		*(token->argv + i) = ft_strdup(prs_argv_list_get_str(tmp));
		tmp = tmp->next;
		i++;
	}
	prs_free_arg_list(argv_list);
}
