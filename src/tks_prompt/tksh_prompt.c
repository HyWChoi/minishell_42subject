/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:50 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/20 16:24:43 by yechakim         ###   ########.fr       */
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


static void	tks_stop_readline(int sig)
{

	(void)sig;
	g_sig_flag = SIGINT_FLAG_ON;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	tksh_sig_hook(void)
{
	struct termios	term;
		
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
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
	else if (*input)
		add_history(input);
	else
	{
		free(input);
		return (NULL);
	}
	return (input);
}
