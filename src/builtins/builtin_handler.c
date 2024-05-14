/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:21:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/13 20:05:56 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static ssize_t builtin_handler_helper_get_cmd(char *cmd){
	ssize_t	cmd_idx;
	char	*builtin_cmds[7] = {CD, ECHO, ENV, EXIT, PWD, UNSET};

	cmd_idx = 0;
	while(cmd_idx < 7)
	{
		if(ft_strncmp(builtin_cmds[cmd_idx], cmd, ft_strlen(builtin_cmds[cmd_idx] + 1)) == 0)
			return (cmd_idx);
		cmd_idx++;
	}
	return (-1);
}

void	builtin_handler(t_token *token){
	t_builtin_dto	*builtin_dtos[7] = {dto_cd, dto_echo, dto_env, dto_exit, dto_pwd, dto_unset};
	const ssize_t	cmd_idx = builtin_handler_helper_get_cmd(token->cmd_path);

	// TODO: 추후 상세한 에러처리 필요
	if(cmd_idx == -1)
	{
		return (void)printf("err");
	}
	return (builtin_dtos[cmd_idx](token));
}
