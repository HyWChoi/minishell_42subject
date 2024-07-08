#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

t_exit_code	dto_unset(t_token *token)
{
	return (unset(token->argv, *(token->envp)));
}