#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	dbg_print_argv(char **argv)
{
	printf("argv: [");
	while (argv && *argv)
	{
		if (*(argv + 1) == NULL)
			printf("`%s`", *argv++);
		else
			printf("`%s`, ", *argv++);
	}
	printf("]\n");
}

void	dbg_print_arg_list(t_argv_list **argv)
{
	t_argv_list	*start;

	start = *argv;
	printf("argv: [");
	while (start)
	{
		if (start->next)
			printf("`%s`, ", start->argv);
		else
			printf("`%s`", start->argv);
		start = start->next;
	}
	printf("]\n");
}

void	dbg_print_token(t_token **token_list)
{
	if (!token_list)
	{
		printf("token_list is EMPTY!\n");
		return ;
	}
	while (*token_list)
	{
		printf("cmd_path: %s\n", (*token_list)->cmd_path);
		dbg_print_argv((*token_list)->argv);
		if ((*token_list)->envp)
			printf("envp[0]: %p -> %s\n", *((*token_list)->envp), **(*token_list)->envp);
			// printf("hihihihihihi\n");
		if ((*token_list)->infile_path)
			printf("infile_path: %s\n", (*token_list)->infile_path);
		if ((*token_list)->outfile_path)
			printf("outfile path: %s\n", (*token_list)->outfile_path);
		(*token_list)->is_append ? printf("append activate\n") : printf("append deactivate\n");
		(*token_list)->is_heredoc ? printf("heredoc activate\n") : printf("heredoc deactivate\n");
		printf("-----------------------------\n");
		token_list++;
	}
}

void	dbg_balanced_test(t_prs_stack **stack_list)
{
	while (*stack_list)
	{
		printf("is_balanced_quotation? -> ");
		prs_is_balanced_quote(*stack_list) ? printf("TRUE\n") : printf("FALSE\n");
		stack_list++;
	}
}
