#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

t_exit_code	dto_pwd(t_token *token)
{
	(void)token;
	return (pwd());
}
