/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 20:10:27 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void    run_cmd(t_token *token, pid_t pid)
{
    char *cmd_abs_path; 
    
    if (is_builtin_cmd(token->cmd_path))
    {
        builtin_handler(token);
        // TODO: signal 처리
        exit(EXIT_SUCCESS);
    }
    cmd_abs_path = get_cmd_path_from_env(token->cmd_path, *token->envp);
    if (execve(cmd_abs_path, token->argv, *token->envp) == -1)
    {
        perror("tksh: error: execve failed\n");
        exit(EXIT_FAILURE);
    }
}