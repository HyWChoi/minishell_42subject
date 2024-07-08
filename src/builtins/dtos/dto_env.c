#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_exit_code	dto_env(t_token *token)
{
	printf("-----token pass through the dto env-----\n");
	if (ft_strncmp(token->cmd_path, "env", 4) == 0)
		env((const char **)*(token->envp));
}
