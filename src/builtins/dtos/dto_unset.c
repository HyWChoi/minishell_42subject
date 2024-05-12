#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

void	dto_unset(t_token *token)
{
	printf("-----token pass through the dto unset-----\n");
	if (ft_strncmp(token->cmd_path, "cd", 3) == 0)
		unset(token->argv, token->envp);
}
