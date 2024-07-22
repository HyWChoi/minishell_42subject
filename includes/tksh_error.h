/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_error.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:29 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 02:46:52 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_ERROR_H
# define TKSH_ERROR_H

void	put_err_msg(char *cmd, char *err_msg);
int		throw_syntax_error(char ***envp);

typedef enum e_error_behavior
{
	EXIT_ON_ERROR = 0,
	CONTINUE_ON_ERROR = 1
}	t_error_behavior;

#endif
