/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:43:06 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/24 10:56:12 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_H
# define TKSH_H

# include "libft.h"
# define TK_HEREDOC_PATH "./."
# define SHELL_NAME "minishell"
# define PROMPT "minishell$ "

/*** CUSTOM IMPORT ***/
# include "tksh_types.h"
/* FOR ERROR*/
# include "tksh_error.h"
/* FOR EXECUTE */
# include "tksh_execute.h"

enum e_sig_status {
	SIGINT_FLAG_OFF = 0,
	SIGINT_FLAG_ON = 1,
};

extern sig_atomic_t	g_sig_flag;

void	tksh_free_token(t_token *token);
void	tksh_free_token_list(t_token **token_list);
void	set_exit_code(t_exit_code exit_code, char ***envp);

#endif
