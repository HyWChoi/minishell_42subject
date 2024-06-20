#ifndef TKSH_EXECUTE_H
# define TKSH_EXECUTE_H

# include "tksh.h"
# include "tksh_parse.h"




void execute(t_token **token_list);
size_t get_token_len(t_token **token_list);

/* UTILS */

typedef struct s_io_fd
{
    int stdin_fd;
    int stdout_fd;
} io_fd_t;

t_bool      is_builtin_cmd(const char *cmd_path);
void        run_cmd(t_token *token, pid_t pid);
io_fd_t     io_store();
void        io_redirection(t_token *token);
void        io_restore(io_fd_t io_fd);



# endif

