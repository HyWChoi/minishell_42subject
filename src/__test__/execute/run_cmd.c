/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/21 01:40:56 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void    run_cmd(t_token *token, pid_t pid)
{
    if (pid != 0) // is parent
        return ;
    // printf("run_cmd zz\n");
    if (is_builtin_cmd(token->cmd_path))
    {
        builtin_handler(token);
        // TODO: signal 처리
        exit(EXIT_SUCCESS);
    }
    else
    {
        // printf("cmd_path: %s\n", token->cmd_path);
        execve("/bin/ls", token->argv, *token->envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
}