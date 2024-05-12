#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	dto_pwd(t_token *token)
{
	printf("-----token pass through the dto cd-----\n");
	if (ft_strncmp(token->cmd_path, "pwd", 4) == 0)
		pwd();
}
