/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:43:06 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/20 16:47:40 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_H
# define TKSH_H

# include "libft.h"
# define TK_HEREDOC_PATH "./."
# define SHELL_NAME "tekkensh"
# define PROMPT "tekkensh$ "

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

#endif
