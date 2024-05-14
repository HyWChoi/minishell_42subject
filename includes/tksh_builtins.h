#ifndef TKSHELL_BUILTINS_H
# define TKSHELL_BUILTINS_H

# include "tksh.h"

# define PWD_MAX_BUFF_SIZE 4096
# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define PWD "pwd"
# define UNSET "unset"
# define EXPORT "export"

typedef void	t_builtin_dto(t_token *tokens);

void    builtin_handler(t_token *token);
void	dto_cd(t_token *token);
void	dto_pwd(t_token *token);
void	dto_echo(t_token *token);
void	dto_env(t_token *token);
void	dto_unset(t_token *token);
void	cd(char *path);
void	pwd(void);
void	env(const char **env);
void	exit_shell(unsigned char exit_code);
void	unset(char **argv, char **envp);
void	echo(char **strings, char *option);

# endif
