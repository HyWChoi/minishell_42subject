#ifndef TKSH_EXECUTE_H
# define TKSH_EXECUTE_H
# include "tksh_types.h"
# include "tksh_parse.h"
# include "tksh_io_utils.h"
# include "tksh_signal.h"

# define HERE_DOC_HEADER "heredoc> "

/* EXECUTE API*/
t_exit_code	execute(t_token **token_list);


/* INTERNAL API*/
t_exit_code	ex_return_exit_code(int status);
t_exit_code	ex_run_singlecmd(t_token *token, t_io_fd io_fd);
void		ex_run_child(t_token *token, t_pipe *pipes, int nth, int ps_len);

/* UTILS */
t_bool		ex_sig_catched(t_io_fd);
t_exit_code	ex_wait_children_ended(int token_len, int last_pid);
t_bool		ex_is_child(pid_t pid);
size_t		get_token_len(t_token **token_list);
t_bool		is_builtin_cmd(const char *cmd_path);
void		run_cmd(t_token *token);
char		*get_cmd_path_from_env(char *cmd, char **envp);
t_bool		ex_fork_error_guard(int pid, char *msg);

/* HERE_DOC */
void		heredoc_hook(t_token **token_list);

#endif
