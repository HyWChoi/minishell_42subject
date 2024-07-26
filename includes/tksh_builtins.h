/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_builtins.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:46 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/27 00:17:04 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_BUILTINS_H
# define TKSH_BUILTINS_H

# include "tksh.h"
# include "tksh_parse.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
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
t_exit_code	cd(t_token *token, char *path);
t_exit_code	pwd(void);
t_exit_code	env(const char **env);
t_exit_code	exit_shell(unsigned char exit_code);
t_exit_code	unset(char **argv, char **envp);
t_exit_code	echo(char **strings, t_bool option);
t_exit_code	export(t_token *token);

// export
t_bool		export_is_correct_key(size_t key_len, char *str, char *key);
int			export_is_exist_env(t_token *token, char *key_name);
t_bool		export_invalid_char(char *str);
t_bool		export_is_valid_key(char *key);
void		free_keys(char *key, char *value);
void		export_replace_value(t_token *token, char *key, char *value);

// cd
void		update_oldpwd(t_token *token);
void		update_pwd(t_token *token, char *new_path,
				char saved_pwd[PWD_MAX_BUFF_SIZE]);
void		update_oldpwd_without_pwd(t_token *token);
void		update_pwd_without_get_path(t_token *token, char *new_path,
				char saved_pwd[PWD_MAX_BUFF_SIZE]);
char		*cd_get_path(char **result);
void		cd_set_path_in_buffer(char *path,
				char saved_pwd[PWD_MAX_BUFF_SIZE]);
void		cd_renew_path(t_token *token, char *new_path,
				char saved_pwd[PWD_MAX_BUFF_SIZE]);
#endif
