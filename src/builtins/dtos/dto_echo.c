#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief echo
 *
 * This function repeats the input string that was entered.
 *
 * @param strings A list of strings that this function repeats on a single line.
 * @param option This option determines whether to add a newline character ('\n')
 * @return void
*/

static t_bool	is_option(char **str)
{
	char *tmp = *str;
	if (!*str)
		return FALSE;
	if (ft_strncmp("-n", *str, 2) == 0)
	{
		tmp++;
		while (*tmp)
		{
			if (*tmp != 'n')
				return (FALSE);
			tmp++;
		}
		return TRUE;
	}
	return FALSE;
}

t_exit_code	dto_echo(t_token *token)
{
	char	*option;
	char	**argv;

	option = "";
	argv = token-> argv + 1;
	printf("-----token pass through the dto echo-----\n");
	while (argv) // NOTE: echo -n -n -n -n -n 같이 -n이 여러개 들어오는 경우 argv를 돌면서 option이 유효한지 판단하여 option을 설정
	{
		if (is_option(argv))
		{
			option = *(argv);
			argv = argv + 1;
		}
		else
			break ;
	}
	return (echo(argv, option));
}
