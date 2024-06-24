#ifndef MS_H
# define MS_H

# include "libft.h"
# define TK_HEREDOC_PATH "/tmp/.tksh_here_doc/"

typedef enum	e_file_type
{
	APPEND,
	HEREDOC,
	IN_FILE,
	OUT_FILE
}	t_file_type;

typedef struct	s_file_list
{
	char				*file_name;
	char				*limiter;
	t_file_type			type;
	int					fd;
	struct s_file_list	*next;
}	t_file_list;

typedef struct	s_token
{
	char		*cmd;
	char		*cmd_path;
	char		**argv;
	char		***envp;
	t_file_list	**file;
}	t_token;

void	tksh_free_token(t_token *token);
void	tksh_free_token_list(t_token **token_list);

#endif
