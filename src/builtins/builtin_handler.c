/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:21:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/08 15:25:04 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static ssize_t builtin_handler_helper_get_cmd(char *cmd){
	ssize_t	cmd_idx;
	char	*builtin_cmds[BUITIN_CMD_AMOUNT] = {CD, ECHO, ENV, EXIT, PWD, UNSET, EXPORT};

	cmd_idx = 0;
	while(cmd_idx < BUITIN_CMD_AMOUNT)
	{
		if(ft_strncmp(builtin_cmds[cmd_idx], cmd, ft_strlen(builtin_cmds[cmd_idx]) + 1) == 0)
			return (cmd_idx);
		cmd_idx++;
	}
	return (-1);
}

t_exit_code	builtin_handler(t_token *token){
	t_builtin_dto	*builtin_dtos[BUITIN_CMD_AMOUNT] = {dto_cd, dto_echo, dto_env, dto_exit, dto_pwd, dto_unset, dto_export};
	const ssize_t	cmd_idx = builtin_handler_helper_get_cmd(token->cmd_path);

	// TODO: 추후 상세한 에러처리 필요
	if (cmd_idx == -1)
		return (ECODE_CMD_NOT_FOUND);
	return (builtin_dtos[cmd_idx](token));
}
