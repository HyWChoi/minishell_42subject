/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execute.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yechakim <yechakim@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/20 23:26:03 by yechakim		  #+#	#+#			 */
/*   Updated: 2024/06/21 00:38:24 by yechakim		 ###   ########seoul.kr  */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include "tksh_execute.h"
#include "tksh_builtins.h"

unsigned char	execute(t_token **token_list)
{
	const t_io_fd	io_fd = io_store();
	size_t			token_len;
	size_t			i;
	pid_t			last_pid;
	t_pipe			pipes;

	i = 0;
	if (!token_list)
		return (2);
	shutout_signal();
	token_len = get_token_len(token_list);
	heredoc_hook(token_list);
	if(ex_sig_catched(io_fd))
		return (1);
	if (token_len == 1)
		return (ex_run_singlecmd(*token_list, io_fd));
	while (i < token_len)
	{
		ex_prepare_pipe(token_len, i, &pipes);
		last_pid = fork();
		if (ex_is_child(last_pid))
		{
			ex_fork_error_guard(last_pid, "fork error");
			ex_run_child(token_list[i], &pipes, i, token_len);
		}
		destroy_pipe(&pipes, i, token_len);
		i++;
	}
	io_restore(io_fd);
	return (ex_wait_children_ended(token_len, last_pid));
}
