#include "tksh.h"
#include "tksh_builtins.h"
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

void	dto_cd(t_token *token)
{
	if (ft_strs_len((const char **)token->argv) == 1)
		cd(getenv("HOME"));
	else if (ft_strs_len((const char **)token->argv) == 2)
		cd(*(token->argv + 1));
	else 
		write(2, "cd: too many arguments\n", 24);
}
