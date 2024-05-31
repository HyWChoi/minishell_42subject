#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief prs_free_stack_list
 *
 * This function frees the memory allocated for the given stack list.
 * It iterates through each stack in the list, freeing the stack's components and the stack itself.
 *
 * @param t_prs_stack** stack_list - Pointer to the stack list to be freed.
 */
void	prs_free_stack_list(t_prs_stack **stack_list)
{
	int	i;

	i = 0;
	while (stack_list[i])
	{
		free((stack_list[i])->stack);
		free((stack_list[i])->ori_str);
		free(stack_list[i]);
		i++;
	}
	free(stack_list);
}

/**
 * @brief prs_free_arg_list
 *
 * This function frees the memory allocated for the given argv list.
 * It iterates through each node in the list, freeing the argv string and the node itself.
 *
 * @param t_argv_list** start - Pointer to the head of the argv list to be freed.
 */
void	prs_free_arg_list(t_argv_list **start)
{
	t_argv_list	*tmp;

	tmp = NULL;
	if (start == NULL || *start == NULL)
		return ;
	while (*start)
	{
		printf("arg: free: %s\n", (*start)->argv);
		tmp = (*start)->next;
		if ((*start)->argv)
			free((*start)->argv);
		free(*start);
		*start = tmp;
	}
}
