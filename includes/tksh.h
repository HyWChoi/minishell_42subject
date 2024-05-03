/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:12:04 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/03 12:28:30 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# define PWD_MAX_BUFF_SIZE 4096
#include "libft.h"

void cd(char *path);
void	pwd(void);
void	env(const char **env);
void	exit_shell(unsigned char exit_code);
void	unset(char **argv, char **envp);

#endif
