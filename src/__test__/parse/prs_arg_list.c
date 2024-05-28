#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_argv_list	*prs_argv_list_new_node(char *str)
{
	t_argv_list	*new;

	new = NULL;
	if (!str)
		return (new);
	if (!ft_calloc_guard((void **)&new, 1, sizeof(t_argv_list)))
		return (NULL);
	new->argv = str;
	new->next = NULL;

	return (new);
}

char	*prs_argv_list_get_str(t_argv_list *argv_list)
{
	if (!argv_list)
		return (NULL);
	return (argv_list->argv);
}

t_argv_list	*prs_argv_list_find_last(t_argv_list **start)
{
	if (start == NULL || *start == NULL)
		return NULL;
	while ((*start)->next)
	{
		start = &(*start)->next;
	}
	return (*start);
}

size_t	prs_argv_list_count(t_argv_list **start)
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
