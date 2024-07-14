/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:23:07 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/14 15:14:52 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"

t_exit_code	exit_shell(unsigned char exit_code)
{
	printf("exit\n");
	exit(exit_code);
	return (exit_code);
}
