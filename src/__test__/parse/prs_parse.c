#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

static t_bool	is_check_err_in_stack(t_prs_stack *stack)
{
	if (stack->err_flag)
		return (TRUE);
	return (FALSE);
}

static void	prs_set_cmd_path_in_token(t_token *token)
{
	if (token->argv && token->argv[0])
		token->cmd_path = ft_strdup(token->argv[0]);
}

static void	*prs_set_token(t_prs_stack *stack, t_token *token)
{
	t_argv_list	*argv_list;
	char	*start;

	argv_list = NULL;
	start = stack->ori_str;
	if (!prs_is_balanced_quote(stack)) // TODO: error handling
		return (NULL);
	while (!stack->err_flag && *stack->ori_str)
	{
		if (prs_is_quote(stack->ori_str))
			prs_argv_list_add_node(prs_remove_quote(stack), &argv_list);
		else if (prs_is_redir(stack->ori_str))
			prs_set_file_path_in_token(token, stack);
		else if (!prs_is_white_space(stack->ori_str))
			prs_argv_list_add_node(prs_make_argv_str(stack), &argv_list);
		else
			stack->ori_str++;
	}
	prs_set_argv_into_token(token, &argv_list, stack);
	stack->ori_str = start;
	return (token);
}

void	prs_set_heredoc_path(t_file_list **start, int *heredoc_count)
{
	printf("start: %p\n", start);
	if (start == NULL || *start == NULL)
		return ;
	while ((*start))
	{
		if ((*start)->type == HEREDOC)
			(*start)->file_name = ft_strjoin_and_free(TK_HEREDOC_PATH, ft_itoa((*heredoc_count)++), FREE_S2);
		start = &(*start)->next;
	}
}

t_token	**prs_parse(char *usr_input, char ***envp)
{
	int			i;
	int			heredoc_count;
	t_token		**token_list;
	t_prs_stack	**stack_list;

	i = 0;
	heredoc_count = 0;
	stack_list = prs_init_stack_list(usr_input, envp);
	token_list = prs_init_token_list(ft_strs_len((const char **)stack_list), envp);
	while (stack_list && stack_list[i])
	{
		if (!prs_set_token(stack_list[i], token_list[i]))
			return (NULL);
		prs_set_cmd_path_in_token(token_list[i]);
		if (is_check_err_in_stack(stack_list[i]))
		{
			tksh_free_token_list(token_list);
			token_list = NULL;
			break ;
		}
		prs_set_heredoc_path(token_list[i]->file, &heredoc_count);
		i++;
	}
	prs_free_stack_list(stack_list);
	return (token_list);
}
