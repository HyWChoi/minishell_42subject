#ifndef MS_H
# define MS_H
# define PWD_MAX_BUFF_SIZE 4096
#include "libft.h"

typedef struct	s_token
{
	char	*cmd_path;
	char	**argv;
	char	***envp;
}	t_token;

void	cd(char *path);
void	pwd(void);
void	env(const char **env);
void	exit_shell(unsigned char exit_code);
void	unset(char **argv, char **envp);
void	echo(char **strings, char *option);

#endif
