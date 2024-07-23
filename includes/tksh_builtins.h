/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_builtins.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:46 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 14:57:45 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_BUILTINS_H
# define TKSH_BUILTINS_H

# include "tksh.h"

# define PWD_MAX_BUFF_SIZE 4096

/**
 * @brief Builtin Command Amount
 *
*/
# define BUITIN_CMD_AMOUNT 7 // export is not implemented yet
# define CD "cd"
# define ECHO_STR "echo"
# define ENV "env"
# define EXIT "exit"
# define PWD "pwd"
# define UNSET "unset"
# define EXPORT "export"
# define DECLARE_EXPORT "declare -x %s\n"

typedef t_exit_code	t_builtin_dto(t_token *tokens);

t_exit_code	builtin_handler(t_token *token);
t_exit_code	dto_cd(t_token *token);
t_exit_code	dto_pwd(t_token *token);
t_exit_code	dto_echo(t_token *token);
t_exit_code	dto_exit(t_token *token);
t_exit_code	dto_env(t_token *token);
t_exit_code	dto_unset(t_token *token);
t_exit_code	dto_export(t_token *token);
t_exit_code	cd(char *path);
t_exit_code	pwd(void);
t_exit_code	env(const char **env);
t_exit_code	exit_shell(unsigned char exit_code);
t_exit_code	unset(char **argv, char **envp);
t_exit_code	echo(char **strings, t_bool option);
t_exit_code	export(t_token *token);

//export
t_bool		export_is_correct_key(size_t key_len, char *str, char *key);
int			export_is_exist_env(t_token *token, char *key_name);
t_bool		export_invalid_char(char *str);
t_bool		export_is_valid_key(char *key);
void		free_keys(char *key, char *value);

#endif
