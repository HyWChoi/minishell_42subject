#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief prs_argv_list_new_node
 *
 * This function creates a new node for the argv list with the given string.
 * It allocates memory for the new node, sets the argv to the given string, and initializes the next pointer to NULL.
 *
 * @param char* str - The string to be stored in the new node.
 * @return t_argv_list* - Pointer to the newly created node, or NULL if allocation fails or str is NULL.
 */
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

/**
 * @brief prs_argv_list_add_node
 *
 * This function adds a new node with the given string to the end of the argv list.
 * If the list is empty, it creates a new head node.
 *
 * @param char* str - The string to be added to the list.
 * @param t_argv_list** head - Pointer to the head of the argv list.
 */
void	prs_argv_list_add_node(char *str, t_argv_list	**head)
{
	t_argv_list	*last;

	if (!*head)
		*head = prs_argv_list_new_node(str);
	else
	{
		last = prs_argv_list_find_last(head);
		last->next = prs_argv_list_new_node(str);
	}
}

/**
 * @brief prs_argv_list_get_str
 *
 * This function returns the string stored in the given argv list node.
 *
 * @param t_argv_list* argv_list - The node from which to retrieve the string.
 * @return char* - The string stored in the node, or NULL if the node is NULL.
 */
char	*prs_argv_list_get_str(t_argv_list *argv_list)
{
	if (!argv_list)
		return (NULL);
	return (argv_list->argv);
}

/**
 * @brief prs_argv_list_find_last
 *
 * This function finds the last node in the given argv list.
 *
 * @param t_argv_list** start - Pointer to the head of the argv list.
 * @return t_argv_list* - Pointer to the last node in the list, or NULL if the list is empty or start is NULL.
 */
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

/**
 * @brief prs_argv_list_count
 *
 * This function counts the number of nodes in the given argv list.
 * It prints and returns the count of nodes in the list.
 *
 * @param t_argv_list** start - Pointer to the head of the argv list.
 * @return size_t - The number of nodes in the list.
 */
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
