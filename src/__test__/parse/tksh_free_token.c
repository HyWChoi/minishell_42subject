#include "tksh.h"
#include <stdlib.h>

void prs_free_file_list(t_file_list **file)
{
	t_file_list	*tmp;

	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		if (tmp->file_name)
			free(tmp->file_name);
		if (tmp->limiter)
			free(tmp->limiter);
		free(tmp);
	}
	free(file);
}
/**
 * @brief tksh_free_token
 *
 * This function frees the memory allocated for a single token.
 * It frees the command path, input and output file paths, argument list, environment variables, and the token itself.
 *
 * @param t_token* token - The token to be freed.
 */
void	tksh_free_token(t_token *token)
{
	if (token->cmd_path)
		free(token->cmd_path);
	if (token->argv)
		ft_free_strs(token->argv);
	if (token->file)
		prs_free_file_list(token->file);
	// if (*token->envp)
	// 	ft_free_strs(*(token->envp));
	free(token);
}

/**
 * @brief tksh_free_token_list
 *
 * This function frees the memory allocated for a list of tokens.
 * It iterates through each token in the list and frees it using tksh_free_token, then frees the token list itself.
 *
 * @param t_token** token_list - The list of tokens to be freed.
 */
void	tksh_free_token_list(t_token **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		tksh_free_token(token_list[i++]);
	free(token_list);
}
