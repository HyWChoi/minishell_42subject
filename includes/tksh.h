#ifndef MS_H
# define MS_H

# include "libft.h"

typedef struct	s_token
{
	char	*cmd_path;
	char	**argv;
	char	***envp;
}	t_token;

#endif
