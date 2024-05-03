/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/03 15:03:47 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include <unistd.h>
#include <stdio.h>

void	pwd(void)
{
	char	buff[PWD_MAX_BUFF_SIZE];

	if (!getcwd(buff, PWD_MAX_BUFF_SIZE))
		printf("getcwd: buffer space is too small to disply the path.\n");
	else
		printf("%s\n", buff);
}
