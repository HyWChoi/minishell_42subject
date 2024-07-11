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
	char	*result;
	char	*tmp;

	argv_list = NULL;
	result = ft_strdup("");
	tmp = NULL;
	start = stack->ori_str;
	if (!prs_is_balanced_quote(stack)) // TODO: error handling
	{
		free(result);
		return (NULL);
	}
	while (!stack->err_flag && *stack->ori_str)
	{
		if (prs_is_quote(stack->ori_str))
			tmp = prs_remove_quote(stack);
		else if (prs_is_redir(stack->ori_str))
		{
			prs_set_file_path_in_token(token, stack);
			if (*result)
			{
				prs_argv_list_add_node(result, &argv_list, stack);
				result = ft_strdup("");
			}
			continue ;
		}
		else if (!prs_is_white_space(stack->ori_str))
			tmp = prs_make_argv_str(stack);
		if (prs_is_white_space(stack->ori_str))
		{
			stack->ori_str++;
			if (tmp)
			{
				result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
				prs_argv_list_add_node(result, &argv_list, stack);
				result = ft_strdup("");
				tmp = NULL;
			}
		}
		else
		{
			result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
			// prs_argv_list_add_node(result, &argv_list);
			// break ;
		}
		if (!*stack->ori_str)
			prs_argv_list_add_node(result, &argv_list, stack);
	}
	if (!(*result))
		free(result);
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

t_token	**prs_parse(char *usr_input, char ***envp)
{
	int			i;
	t_token		**token_list;
	t_prs_stack	**stack_list;

	i = 0;
	stack_list = prs_init_stack_list(usr_input, envp);
	token_list = prs_init_token_list(ft_strs_len((const char **)stack_list), envp);
	while (stack_list && stack_list[i])
	{
		if (!prs_set_token(stack_list[i], token_list[i]))
		{
			free(usr_input);
			prs_free_stack_list(stack_list);
			tksh_free_token_list(token_list);
			return (NULL);
		}
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
