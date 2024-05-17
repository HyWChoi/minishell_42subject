#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

void	dto_exit(t_token *token)
{
	size_t argc;
	char *exit_str;
	
	if (*token->argv == NULL)
		exit_shell(0);
	exit_str = token->argv[0];
	argc = ft_strs_len((const char **)token->argv);
	while (*exit_str)
	{
		if (!ft_isdigit(*exit_str))
		{
			printf("exit: %s: numeric argument required\n", *(token->argv));
			exit_shell(255);
		}
		exit_str++;
	}
	if (2 <= argc) // TODO: argv의 구성에 따라 개수가 달라져야함
	{
		printf("exit: too many arguments\n");
		// TODO: 시그널 처리 필요
		return ;
	}
	printf("-----token pass through the dto exit-----\n");
	if (ft_strncmp(token->cmd_path, "exit", 5) == 0)
		exit((unsigned char)ft_atoi(token->argv[0]));
}

