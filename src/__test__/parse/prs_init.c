#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"

t_token	**prs_init_token_list(size_t size, char ***envp)
{
	size_t	i;
	t_token	**token_list;

	token_list = NULL;
	i = 0;
	if (!ft_calloc_guard((void **)&token_list, size + 1, sizeof(t_token *)))
		return (NULL);
	while (i < size)
	{
		prs_init_token(token_list + i, envp);
		i++;
	}
	return (token_list);
}

void	prs_init_token(t_token **token, char	***envp)
{
	if (!ft_calloc_guard((void **)token, 1, sizeof(t_token)))
		return ;
	(*token)->cmd_path = NULL;
	(*token)->argv = NULL;
	(*token)->envp = envp;
	(*token)->infile_path = NULL;
	(*token)->outfile_path = NULL;
	(*token)->is_append = FALSE;
	(*token)->is_heredoc = FALSE;
}

t_prs_stack	**prs_init_stack_list(char *ori_str, char ***envp)
{
	char	**splited_strs;
	size_t	splited_num;
	size_t	i;
	t_prs_stack	**parse_list;

	i = 0;
	parse_list = NULL;
	splited_strs = ft_split((const char *)ori_str, PRS_PIPE);
	splited_num = ft_strs_len((const char **)splited_strs);
	if (!ft_calloc_guard((void **)&parse_list, splited_num + 1, sizeof(t_prs_stack *)))
		return (NULL);
	while (i < splited_num)
	{
		prs_stack_init(&parse_list[i], splited_strs[i], envp);
		i++;
	}
	ft_free_strs(splited_strs);
	return (parse_list);
}

void	prs_stack_init(t_prs_stack	**stack, char *ori_str, char ***envp)
{
	size_t	size;

	if(!ft_calloc_guard((void **)stack, 1, sizeof(t_prs_stack)))
		return ;
	(*stack)->ori_str = ft_strtrim((const char *)ori_str, PRS_WHITE_SPACE);
	size = ft_strlen((const char *)(*stack)->ori_str);
	if(!ft_calloc_guard((void **)&((*stack)->stack), size + 1, sizeof(char *)))
		return ;
	(*stack)->envp = envp;
	(*stack)->top = -1;
	(*stack)->size = size;
	(*stack)->is_double_quote = FALSE;
	(*stack)->is_single_quote = FALSE;
	(*stack)->err_flag = FALSE;
}
