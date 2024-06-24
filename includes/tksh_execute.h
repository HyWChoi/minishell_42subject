#ifndef TKSH_EXECUTE_H
# define TKSH_EXECUTE_H

# include "tksh.h"
# include "tksh_parse.h"

void		execute(t_token **token_list);
size_t		get_token_len(t_token **token_list);

/* UTILS */

typedef struct s_io_fd
{
	int stdin_fd;
	int stdout_fd;
} io_fd_t;

io_fd_t		io_store();
t_bool		is_builtin_cmd(const char *cmd_path);
void		run_cmd(t_token *token, pid_t pid);
void		io_redirection(t_token *token);
void		io_restore(io_fd_t io_fd);
char		*get_cmd_path_from_env(char *cmd, char **envp);
void		ex_fork_error_guard(int pid, char *msg);


/* HERE_DOC */
# define HERE_DOC_HEADER "heredoc> "

void heredoc_hook(t_token **token_list);

# endif

