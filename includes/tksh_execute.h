#ifndef TKSH_EXECUTE_H
# define TKSH_EXECUTE_H

# include "tksh.h"
# include "tksh_parse.h"


t_exit_code		execute(t_token **token_list);
size_t		get_token_len(t_token **token_list);

/* UTILS */

typedef struct s_io_fd
{
	int stdin_fd;
	int stdout_fd;
} io_fd_t;

typedef struct s_pipe
{
	int prev[2];
	int curr[2];
} t_pipe;

typedef enum e_pipe
{
	FD_IN,
	FD_OUT
}			t_pipe_fd;



io_fd_t		io_store();
t_bool		is_builtin_cmd(const char *cmd_path);
void		run_cmd(t_token *token);
void		io_redirection(t_token *token);
void		io_restore(io_fd_t io_fd);
char		*get_cmd_path_from_env(char *cmd, char **envp);
void		ex_fork_error_guard(int pid, char *msg);
void		ex_move_2fd(int from, int to);
void		ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes);
void		destroy_pipe(t_pipe *pipe, int i, int cmd_cnt);
void		pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len);


/* HERE_DOC */
# define HERE_DOC_HEADER "heredoc> "

void heredoc_hook(t_token **token_list);

# endif

