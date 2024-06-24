/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:35 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 18:05:57 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "tksh_parse.h"

void heredoc(char *filename, char *limiter)
{
	int fd;
	char *line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	while (1)
	{
		line = readline(HERE_DOC_HEADER);
		if (line == NULL)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
	}
	close(fd);
}


void heredoc_hook(t_token **token_list)
{
	t_file_list	*file_list;

	t_file_list = NULL;
	while (*token_list)
	{
		if ((*token_list)->file)
			file_list = (*(*token_list)->file);
		while (file_list)
		{
			if (file_list->type == HEREDOC)
				heredoc(file_list->file_name, file_list->limiter);
			file_list = file_list->next;
		}
		token_list++;
	}
}

