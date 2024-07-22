/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:14:12 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/23 06:14:25 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_PROMPT_H
# define TKSH_PROMPT_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <signal.h>
# include <termios.h>
# include "get_next_line.h"

char	*tksh_prompt(void);
void	exit_on_eof(void);

#endif
