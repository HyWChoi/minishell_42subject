/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 21:55:43 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void    run_cmd(t_token *token)
{
    char *cmd_abs_path; 
  
    cmd_abs_path = get_cmd_path_from_env(token->cmd_path, *token->envp);
    if (execve(cmd_abs_path, token->argv, *token->envp) == -1)
    {
        perror(token->cmd_path);
        exit(EXIT_FAILURE);
    }
}