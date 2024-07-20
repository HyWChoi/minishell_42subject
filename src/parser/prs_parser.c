/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:19:27 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/20 16:38:25 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	prs_init_stack_token_lists(t_prs_stack ***stack_list,
		t_token ***token_list, char *usr_input, char ***envp)
{
	char	*trimed_input;

	trimed_input = ft_strtrim(usr_input, PRS_WHITE_SPACE);
	if (*trimed_input == '\0' || *trimed_input == '|'
		|| *(trimed_input + ft_strlen(trimed_input) - 1) == '|')
	{
		free(trimed_input);
		*stack_list = NULL;
		*token_list = NULL;
		return ;
	}
	*stack_list = prs_init_stack_list(trimed_input, envp);
	*token_list = prs_init_token_list(ft_strs_len((const char **)*stack_list),
			envp);
	free(trimed_input);
}

t_token	**prs_parse(char *usr_input, char ***envp)
{
	t_prs_stack	**stack_list;
	t_token		**token_list;
	int			i;

	i = 0;
	if (!prs_is_balanced_quote(usr_input))
		return (handle_unbalanced_quote(usr_input));
	prs_init_stack_token_lists(&stack_list, &token_list, usr_input, envp);
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
	prs_set_heredoc_path(token_list);
	free(usr_input);
	return (token_list);
}
