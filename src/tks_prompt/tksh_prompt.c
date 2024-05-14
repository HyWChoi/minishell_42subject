/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:50 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/14 17:48:06 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_prompt.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

static int	tks_rl_event_hook_placeholder(void)
{
	return (0);
}

static void	tks_stop_readline(int sig)
{
	struct termios	term;

	(void)sig;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_redisplay();
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

static void	tksh_sig_hook(void)
{
	rl_event_hook = tks_rl_event_hook_placeholder;
	signal(SIGINT, tks_stop_readline);
	signal(SIGQUIT, SIG_IGN);
}

char	*tksh_prompt(char *envp)
{
	char	*input;

	(void)envp;
	tksh_sig_hook();
	input = readline(PROMPT);
	if (!input)
		exit(0); // TODO: 상세한 에러처리 필요
	if (*input)
		add_history(input);
	return (input);
}
