#ifndef TKSH_EXECUTE_H
# define TKSH_EXECUTE_H
# include "tksh_types.h"
# include "tksh_parse.h"
# include "tksh_io_utils.h"
# define HERE_DOC_HEADER "heredoc> "

t_exit_code	execute(t_token **token_list);
size_t		get_token_len(t_token **token_list);

/* UTILS */
t_bool		is_builtin_cmd(const char *cmd_path);
void		run_cmd(t_token *token);
char		*get_cmd_path_from_env(char *cmd, char **envp);
void		ex_fork_error_guard(int pid, char *msg);

/* HERE_DOC */
void		heredoc_hook(t_token **token_list);

#endif
