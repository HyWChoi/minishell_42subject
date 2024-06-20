/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:26:03 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/21 00:38:24 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void    execute(t_token **token_list)
{
    const size_t token_len = get_token_len(token_list);
    const io_fd_t io_fd = io_store(); // io save function is save parents's io fd

    if (token_len == 1 && is_builtin_cmd(token_list[0]-> cmd_path))
        return (builtin_handler(*token_list));
    while(*token_list)
    {
        // io_redirection(*token_list);
        if(token_len == 1 && is_builtin_cmd((*token_list)->cmd_path))
            builtin_handler(*token_list);
        else
        {
            pid_t pid = fork();
            run_cmd(*token_list, pid);
            if(pid != 0)
                waitpid(pid, NULL, 0);
        }
        io_restore(io_fd);
        token_list++;
    }
    
    // printf("in execute\n");
    // printf("token_len: %zu\n", token_len);

}
