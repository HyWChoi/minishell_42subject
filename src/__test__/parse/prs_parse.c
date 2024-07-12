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

static char	*prs_process_quote(t_prs_stack *stack)
{
	return (prs_remove_quote(stack));
}

static void	prs_process_redir(t_token *token,
		t_argv_list **argv_list, t_prs_stack *stack, char **result)
{
	prs_set_file_path_in_token(token, stack);
	if (**result)
	{
		prs_argv_list_add_node(*result, argv_list, stack);
		*result = ft_strdup("");
	}
}

static char	*prs_process_regular_char(t_prs_stack *stack)
{
	return (prs_make_argv_str(stack));
}

static void	*handle_unbalanced_quote(char *result)
{
	free(result);
	return (NULL);
}

static char	*prs_handle_whitespace(t_prs_stack *stack,
		char *tmp, char *result, t_argv_list **argv_list)
{
	if (prs_is_white_space(stack->ori_str))
	{
		stack->ori_str++;
		if (tmp)
		{
			result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
			prs_argv_list_add_node(result, argv_list, stack);
			result = ft_strdup("");
		}
	}
	else
		result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
	if (!*stack->ori_str)
	{
		prs_argv_list_add_node(result, argv_list, stack);
		result = ft_strdup("");
	}
	return (result);
}

static char	*prs_process_stack(t_prs_stack *stack,
		t_token *token, char *result, t_argv_list **argv_list)
{
	char	*tmp;

	tmp = NULL;
	if (prs_is_quote(stack->ori_str))
		tmp = prs_process_quote(stack);
	else if (prs_is_redir(stack->ori_str))
	{
		prs_process_redir(token, argv_list, stack, &result);
		return (result);
	}
	else if (!prs_is_white_space(stack->ori_str))
		tmp = prs_process_regular_char(stack);
	result = prs_handle_whitespace(stack, tmp, result, argv_list);
	return (result);
}

static void	finalize_result(char *result,
		t_argv_list **argv_list, t_prs_stack *stack)
{
	if (!(*result))
		free(result);
	else
	{
		prs_argv_list_add_node(result, argv_list, stack);
		free(result);
	}
}

void	*prs_set_token(t_prs_stack *stack, t_token *token)
{
	t_argv_list	*argv_list;
	char		*start;
	char		*result;

	argv_list = NULL;
	result = ft_strdup("");
	start = stack->ori_str;
	if (!prs_is_balanced_quote(stack))
		return (handle_unbalanced_quote(result));
	while (!stack->err_flag && *stack->ori_str)
		result = prs_process_stack(stack, token, result, &argv_list);
	finalize_result(result, &argv_list, stack);
	prs_set_argv_into_token(token, &argv_list, stack);
	stack->ori_str = start;
	return (token);
}

void	set_heredoc_path(t_token **token)
{
	t_file_list	*file_list;
	int			count;

	count = 0;
	while (token && *token)
	{
		file_list = *(*token)->file;
		while (file_list)
		{
			if (file_list->type == HEREDOC)
			{
				file_list->file_name = prs_make_heredoc_file(count);
				count++;
			}
			file_list = file_list->next;
		}
		token++;
	}
}

void	*prs_err_free_all(char *usr_input,
		t_prs_stack **stack_list, t_token **token_list)
{
	free(usr_input);
	prs_free_stack_list(stack_list);
	tksh_free_token_list(token_list);
	return (NULL);
}

t_token	**prs_parse(char *usr_input, char ***envp)
{
	int			i;
	t_token		**token_list;
	t_prs_stack	**stack_list;

	i = 0;
	stack_list = prs_init_stack_list(usr_input, envp);
	token_list = prs_init_token_list(ft_strs_len((const char **)stack_list),
			envp);
	while (stack_list && stack_list[i])
	{
		if (!prs_set_token(stack_list[i], token_list[i]))
			return (prs_err_free_all(usr_input, stack_list, token_list));
		prs_set_cmd_path_in_token(token_list[i]);
		if (is_check_err_in_stack(stack_list[i]))
		{
			tksh_free_token_list(token_list);
			token_list = NULL;
			break ;
		}
		i++;
	}
	prs_free_stack_list(stack_list);
	set_heredoc_path(token_list);
	free(usr_input);
	return (token_list);
}
