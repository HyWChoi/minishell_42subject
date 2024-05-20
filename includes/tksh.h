#ifndef MS_H
# define MS_H

# include "libft.h"

typedef struct	s_token
{
	char	*cmd_path;
	char	**argv;
	char	***envp;
	char	*infile_path;
	char	*outfile_path;
	t_bool	is_append;
	t_bool	is_heredoc;
}	t_token;

#endif
