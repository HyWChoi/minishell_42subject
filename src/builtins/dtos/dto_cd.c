#include "tksh.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief change directory dto
 *
 * This function
 * to the path specified by the argunment.
 *
 * @param path The path to change the current working directory to.
 * @return void
*/

t_exit_code	dto_cd(t_token *token)
{
	char	*result_home;
	t_exit_code	code;
	if (ft_strs_len((const char **)token->argv) == 1)
	{
		result_home = NULL;
		result_home = prs_parse_variable("$HOME", token->envp);
		if (!*result_home)
		{
			free(result_home);
			printf("tksh: cd: HOME not set\n");
			return (1);
		}
		code = cd(result_home);
		free(result_home);
		return (code);
	}
	else if (ft_strs_len((const char **)token->argv) == 2)
		return (cd(*(token->argv + 1)));
	else {
		write(2, "cd: too many arguments\n", 24);
		return (1);
	}
}
