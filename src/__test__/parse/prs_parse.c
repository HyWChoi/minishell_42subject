#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	free_token(t_token *token)
{
	if (token->cmd_path)
		free(token->cmd_path);
	if (token->infile_path)
		free(token->infile_path);
	if (token->outfile_path)
		free(token->outfile_path);
	if (token->argv)
		ft_free_strs(token->argv);
	// if (*token->envp)
	// 	ft_free_strs(*(token->envp));
	free(token);
}

void	free_token_list(t_token **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		free_token(token_list[i++]);
	free(token_list);
}

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

t_token	**prs_parse(char *usr_input, char ***envp)
{
	int	i;
	t_token	**token_list;
	t_prs_stack	**stack_list;

	i = 0;
	stack_list = prs_init_stack_list(usr_input, envp);
	token_list = prs_init_token_list(ft_strs_len((const char **)stack_list), envp);
	while (stack_list[i])
	{
		prs_set_token(stack_list[i], token_list[i]);
		if (stack_list[i]->err_flag)
		{
			// free_token_list(token_list);
			token_list = NULL;
			break ;
		}
		if (token_list[i]->argv)
			token_list[i]->cmd_path = ft_strdup(*token_list[i]->argv);
		i++;
	}
	prs_free_stack_list(stack_list);
	return (token_list);
}

char	*prs_find_value_in_envp(char *str, char ***envp)
{
	const size_t	len = ft_strlen(str);
	t_bool			is_found;
	size_t			i;

	i = 0;
	is_found = FALSE;
	while (*envp[i])
	{
		if (ft_strncmp(*envp[i], str, len) == 0)
		{
			is_found = TRUE;
			break ;
		}
		i++;
	}
	free(str);
	if (is_found)
		return (*envp[i] + len);
	return (NULL);
}

char	*prs_find_envp(char *str, char ***envp)
{
	char	*start;
	char	*envp_value;
	char	*result;
	size_t	i;

	i = 0;
	start = str;
	while (*start && !prs_is_variable(start))
		start++;
	result = ft_strndup(start, start - str - 1);
	if (prs_is_variable(start) && prs_is_possible_var_space(start + 1))
	{
		str++;
		while (*(start + i) && prs_is_possible_var_name(start + i))
			i++;
		envp_value = ft_strjoin_and_free(ft_strndup(start, i - 1), "=", FREE_S1);
		envp_value = prs_find_value_in_envp(envp_value, envp);
		if (envp_value)
			result = ft_strjoin_and_free(result, envp_value, FREE_BOTH);
	}
	result = ft_strjoin_and_free(result, ft_strdup(start + i), FREE_S1);
	free(str);
	return (result);
}

void	prs_set_token(t_prs_stack *stack, t_token *token)
{
	t_argv_list	*argv_list;
	char	*start;

	argv_list = NULL;
	start = stack->ori_str;
	if (!prs_is_balanced_quote(stack))
		return ((void)printf("unblanced qoutation\n"));
	while (!stack->err_flag && *stack->ori_str)
	{
		printf("? %s ?\n", stack->ori_str);
		if (prs_is_quote(stack->ori_str))
			prs_add_argv_in_token(prs_remove_quote(stack, token->envp), &argv_list);
		else if (prs_is_redir(stack->ori_str))
			prs_add_file_in_token(token, stack);
		else if (!prs_is_white_space(stack->ori_str))
			prs_add_argv_in_token(prs_make_argv(stack, token->envp), &argv_list);
		else
			stack->ori_str++;
	}
	prs_set_argv_in_token(token, &argv_list, stack);
	stack->ori_str = start;
}
