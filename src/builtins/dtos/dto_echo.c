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

static int	is_option(char *str)
{
	if (ft_strncmp("-n", str, 2) == 0)
		return TRUE;
	return FALSE;
}

void	dto_echo(t_token *token)
{
	char	*option;

	printf("-----token pass through the dto echo-----\n");
	if (!is_option(*(token->argv)))
		option = NULL;
	else
		option = *(token->argv);
	if (ft_strncmp(token->cmd_path, "echo", 2) == 0)
		echo(token->argv + 1, option);
}
