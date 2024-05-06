/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:23:07 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/06 14:28:56 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"

/**
 * @brief exit shell
 *
 * This function is called when the user types the exit command.
 *
 * @param exit_code exit code that will be ranged from 0 to 255
 * @return void
*/
void	exit_shell(unsigned char exit_code)
{
	exit(exit_code);
}
