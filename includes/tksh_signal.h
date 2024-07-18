/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:39:35 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:39:35 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_SIGNAL_H
# define TKSH_SIGNAL_H

# include <signal.h>

void	shutout_signal(void);
void	reset_signal(void);

#endif
