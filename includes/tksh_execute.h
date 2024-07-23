/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_execute.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:41:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 15:54:51 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_exit_code	ex_run_singlecmd(t_token *token);
void		ex_run_child(t_token *token, t_pipe *pipes, int nth, int ps_len);

/* UTILS */
t_bool		ex_sig_catched(t_io_fd io_fd);
t_exit_code	ex_wait_children_ended(int token_len, int last_pid);
t_bool		ex_is_child(pid_t pid);
size_t		get_token_len(t_token **token_list);
t_bool		is_builtin_cmd(const char *cmd_path);
void		run_cmd(t_token *token);
char		*get_cmd_path_from_env(char *cmd, char **envp);
t_bool		ex_fork_error_guard(int pid, char *msg);

/* HERE_DOC */
int			heredoc_rl_event_hook(void);
void		heredoc_stop_readline(int sig);
void		heredoc_signal_hook(void);
char		*expand_line(char *line, char ***envp);
t_bool		heredoc_need_stop(char *line, char *limiter);
int			heredoc(char *filename, char *limiter, char ***envp, t_bool expand);
void		heredoc_hook(t_token **token_list);

#endif
