/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:21:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/06 14:18:34 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include <stdlib.h>

static ssize_t builtin_hander_helper_get_cmd(char *cmd){
	ssize_t	cmd_idx;
	char	*bultin_cmds = {CD, ECHO, ENV, EXIT, PWD, UNSET};

	cmd_idx = 0;
	while(cmd_idx < 7)
	{
		if(ft_strncmp(bultin_cmds, cmd, ft_strlen(bultin_cmds)+1) == 0)
			return (cmd_idx);
		cmd_idx++;
	}
	return (-1);
}

void	builtin_hander(t_token *token){
	t_builtin_dto	*builtin_dtos[7] = {cd, echo, env, exit, pwd, unset};
	char			*bultin_cmds = {CD, ECHO, ENV, EXIT, PWD, UNSET};
	const ssize_t	cmd_idx = builtin_hander_helper_get_cmd(token->cmd_path);

	// TODO: 추후 상세한 에러처리 필요
	if(cmd_idx == -1)
		return (void)printf("err");
	return (builtin_dtos[cmd_idx](token));
}
