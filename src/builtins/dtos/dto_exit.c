#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

void	dto_exit(t_token *token)
{
	printf("-----token pass through the dto dto-----\n");
	if (ft_strncmp(token->cmd_path, "exit", 5) == 0)
		exit(SIGKILL); // 임시로 넣은 SIG 추후 개선 필요
}
