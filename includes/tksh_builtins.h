#ifndef TKSHELL_BUILTINS_H
# define TKSHELL_BUILTINS_H

# include "tksh.h"

# define PWD_MAX_BUFF_SIZE 4096

/** 
 * @brief Builtin Command Amount
 * 
*/
# define BUITIN_CMD_AMOUNT 7 // export is not implemented yet
# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define PWD "pwd"
# define UNSET "unset"
# define EXPORT "export"
# define DECLARE_EXPORT "declare -x %s\n"

typedef t_exit_code	t_builtin_dto(t_token *tokens);

t_exit_code	builtin_handler(t_token *token);
t_exit_code	dto_cd(t_token *token);
t_exit_code	dto_pwd(t_token *token);
t_exit_code	dto_echo(t_token *token);
t_exit_code	dto_exit(t_token *token);
t_exit_code	dto_env(t_token *token);
t_exit_code	dto_unset(t_token *token);
t_exit_code	dto_export(t_token *token);
t_exit_code	cd(char *path);
t_exit_code	pwd(void);
t_exit_code	env(const char **env);
t_exit_code	exit_shell(unsigned char exit_code);
t_exit_code	unset(char **argv, char **envp);
t_exit_code	echo(char **strings, char *option);
t_exit_code	export(t_token *token);

#endif
