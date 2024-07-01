/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:47:10 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/21 00:41:32 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "tksh_builtins.h"
#include "libft.h" 

t_bool is_builtin_cmd(const char *cmd_path)
{
    const char *builtin_cmds[BUITIN_CMD_AMOUNT] = {CD, ECHO, ENV, EXIT, PWD, UNSET};
    size_t idx = 0;

    while (idx < BUITIN_CMD_AMOUNT)
    {
        if (ft_strncmp(builtin_cmds[idx], cmd_path, ft_strlen(builtin_cmds[idx]) + 1) == 0)
            return (TRUE);
        idx++;
    }
    return (FALSE);
}

