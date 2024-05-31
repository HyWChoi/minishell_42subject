#include "tksh.h"
#include <stdlib.h>

void	tksh_free_token(t_token *token)
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

void	tksh_free_token_list(t_token **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		tksh_free_token(token_list[i++]);
	free(token_list);
}
