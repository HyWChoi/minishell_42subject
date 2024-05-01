/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/01 18:07:56 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tksh.h"
#include <unistd.h>
#include <stdio.h>

void	pwd(void)
{
	char	buff[MAX_BUFF_SIZE];

	if (!getcwd(buff, MAX_BUFF_SIZE))
	{
		printf("getcwd: buffer space is too small to disply the path.\n");
		exit(1);
	}
	printf("%s\n", buff);
}
