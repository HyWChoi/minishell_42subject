/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/06/03 19:19:57 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief prs_qoute
 *
 * 일단 스택에 하나 씩 담으면서 가다가 ", ', `만나면 스택에 넣고 이전꺼까진 push하자
 * 근데 띄어쓰기는 제거하고 넣어주는게 맞을듯
 * 그러나 ", ', ` 안에 있는 띄어쓰기는 그대로 넣어주자
 * qoute 요약
단일 따옴표 (''):

문자열을 그대로 리터럴로 처리.
메타문자 해석하지 않음.
이스케이프 문자도 무시.
이중 따옴표 (""):

문자열 내부의 $, \, ```, 및 !는 특별하게 처리.
나머지 메타문자는 해석하지 않음.
백틱 (``):

명령어 치환 수행.
명령어 실행 결과가 해당 위치에 삽입됨
 *
*/

/**
 * @brief main of parse test
 * IMPORTANT: This is a MAIN Function of "prs_test"
*/
int main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	(void)argc;
	(void)argv;

	token_list = NULL;
	char **tmp = ft_strs_copy(initial_envp);
	envp = &tmp;
	while (1)
	{
		char *origin_str = tksh_prompt(**envp);
		token_list = prs_parse(origin_str, envp);
		dbg_print_token(token_list);
		if (token_list)
		{
			tksh_free_token_list(token_list);
		}
	}
	return (0);
}
