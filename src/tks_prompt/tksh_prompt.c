/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:50 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/19 08:52:24 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_prompt.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

int eof_flag = 0;

static int	tks_rl_event_hook_placeholder(void)
{
	if(isatty(0) == 0)
		exit(0);
	return (0);
}

static void	tks_stop_readline(int sig)
{
	// struct termios	term;

	(void)sig;
	rl_done = 1;
	g_sig_flag = SIGINT_FLAG_ON;
	
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	tksh_sig_hook(void)
{
	struct termios	term;
		
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	rl_event_hook = tks_rl_event_hook_placeholder;
	signal(SIGINT, tks_stop_readline);
	signal(SIGQUIT, SIG_IGN);
}

char	*tksh_prompt(char *envp)
{
	char	*input;
	

	(void)envp;
	tksh_sig_hook();
	if(eof_flag)
	{
		eof_flag = 0;
		exit(0);
	}
	input = readline(PROMPT);
	if (!input)
		exit(0); // TODO: 상세한 에러처리 필요
	else if (*input)
		add_history(input);
	else
	{
		free(input);
		return (NULL);
	}
	return (input);
}
