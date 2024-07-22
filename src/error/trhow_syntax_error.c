/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trhow_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:40:23 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/23 02:45:07 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_error.h"

int	throw_syntax_error(char ***envp)
{
	ft_putstr_fd(SHELL_NAME": Syntax Error\n", 2);
	set_exit_code(2, envp);
	return (2);
}
