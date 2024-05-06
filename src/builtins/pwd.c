/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/06 14:29:02 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

void	pwd(void)
{
	char	buff[PWD_MAX_BUFF_SIZE];

	if (!getcwd(buff, PWD_MAX_BUFF_SIZE))
		perror("pwd");
	else
		printf("%s\n", buff);
}
