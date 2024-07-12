#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

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

void	prs_free_arg_list(t_argv_list **start)
{
	t_argv_list	*tmp;

	while (*start)
	{
		tmp = *start;
		*start = (*start)->next;
		if (tmp->argv)
			free(tmp->argv);
		free(tmp);
	}
}
