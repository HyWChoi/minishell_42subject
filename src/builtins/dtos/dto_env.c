#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_exit_code	dto_env(t_token *token)
{
	return (env((const char **)*(token->envp)));
}
