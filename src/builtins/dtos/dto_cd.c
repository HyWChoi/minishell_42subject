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
	printf("-----token pass through the dto cd-----\n");
	if (ft_strncmp(token->cmd_path, "cd", 2) == 0)
		cd(*(token->argv));
}
