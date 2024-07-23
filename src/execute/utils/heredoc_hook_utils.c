/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_hook_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:35 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 20:34:14 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "tksh_parse.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>
#include "get_next_line.h"

int	heredoc_rl_event_hook(void)
{
	struct termios	term;

	if (g_sig_flag == SIGINT_FLAG_ON)
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
		return (0);
	}
	return (0);
}

void	heredoc_stop_readline(int sig)
{
	(void)sig;
	rl_done = 1;
	g_sig_flag = SIGINT_FLAG_ON;
}

void	heredoc_signal_hook(void)
{
	rl_event_hook = heredoc_rl_event_hook;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_stop_readline);
}

char	*expand_line(char *line, char ***envp)
{
	char	*ret;

	ret = prs_parse_variable(line, envp);
	free(line);
	return (ret);
}

t_bool	heredoc_need_stop(char *line, char *limiter)
{
	if (!line)
		return (TRUE);
	if (g_sig_flag == SIGINT_FLAG_ON)
	{
		free(line);
		return (TRUE);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
	{
		free(line);
		return (TRUE);
	}
	return (FALSE);
}
