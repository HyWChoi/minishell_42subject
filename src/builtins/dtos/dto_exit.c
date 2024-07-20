/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:36 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/20 16:53:50 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static t_exit_code	exit_print_err(t_token *token)
{
	ft_putstr_fd(SHELL_NAME "exit: ", STDERR_FILENO);
	ft_putstr_fd(token->argv[1], STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

t_exit_code	dto_exit(t_token *token)
{
	size_t	argc;
	char	*exit_str;

	if (token->argv[1] == NULL)
		exit_shell(0);
	exit_str = token->argv[1];
	argc = ft_strs_len((const char **)token->argv);
	while (*exit_str)
	{
		if (!ft_isdigit(*exit_str) && *exit_str != '-' && *exit_str != '+')
		{
			ft_putstr_fd(SHELL_NAME "exit: ", STDERR_FILENO);
			ft_putstr_fd(token->argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_shell(255);
		}
		exit_str++;
	}
	if (2 < argc)
		return (exit_print_err(token));
	return (exit_shell((unsigned char)ft_atoi(token->argv[1])));
}
