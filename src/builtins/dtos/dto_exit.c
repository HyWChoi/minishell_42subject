#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

t_exit_code	dto_exit(t_token *token)
{
	size_t argc;
	char *exit_str;
	
	if (token->argv[1] == NULL)
		exit_shell(0);
	exit_str = token->argv[1];
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
	if (2 < argc) 
	{
		printf("exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	return (exit_shell((unsigned char)ft_atoi(token->argv[1])));
}

