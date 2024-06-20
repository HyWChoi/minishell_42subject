#ifndef MS_H
# define MS_H

# include "libft.h"

typedef enum	e_type
{
	APPEND,
	HEREDOC,
	IN_FILE,
	OUT_FILE
}	t_type;

typedef struct	s_file_list
{
	char	*file_name;
	t_type	type;
	int		fd;
}	t_file_list;

typedef struct	s_token
{
	char		*cmd_path;
	char		**argv;
	char		***envp;
	t_file_list	*file;
}	t_token;

void	tksh_free_token(t_token *token);
void	tksh_free_token_list(t_token **token_list);

#endif
