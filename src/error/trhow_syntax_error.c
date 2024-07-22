/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trhow_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:40:23 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/22 17:41:55 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_error.h"

int	throw_syntax_error(void)
{
	ft_putstr_fd(SHELL_NAME": Syntax Error\n", 2);
	return (2);
}
