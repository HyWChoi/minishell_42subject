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

void	dto_echo(t_token *token)
{
	char	*option;

	printf("-----token pass through the dto echo-----\n");
	if (!is_option(token->argv))
		option = "";
	else
	{
		option = *(token->argv);
		token->argv = token->argv + 1;
	}
	if (ft_strncmp(token->cmd_path, "echo", 5) == 0)
		echo(token->argv, option);
}
