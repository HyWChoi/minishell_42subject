/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/30 17:15:51 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void    run_cmd(t_token *token)
{
    char *cmd_abs_path; 
  
    cmd_abs_path = get_cmd_path_from_env(token->cmd_path, *token->envp);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (execve(cmd_abs_path, token->argv, *token->envp) == -1)
    {
        printf("%s\n\n", cmd_abs_path); // TODO: signal error 처리
        perror("error in run cmd");
        exit(EXIT_FAILURE);
    }
}