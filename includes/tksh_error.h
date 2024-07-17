#ifndef TKSH_ERROR_H
# define TKSH_ERROR_H

void	put_err_msg(char *cmd, char *err_msg);

typedef enum e_error_behavior
{
	EXIT_ON_ERROR = 0,
	CONTINUE_ON_ERROR = 1
}	t_error_behavior;

#endif
