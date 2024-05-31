#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_is_pipe(char *c)
{
	return (PRS_PIPE == *c);
}

t_bool	prs_is_white_space(char *c)
{
	return (ft_strchr(PRS_WHITE_SPACE, *c) != NULL);
}

t_bool	prs_is_variable(char *c)
{
	return (*c == PRS_VARIABLE);
}

t_bool	prs_is_underbar(char *c)
{
	return (*c == PRS_UNDERBAR);
}

t_bool	prs_is_possible_var_space(char *c)
{
	return (ft_isalpha(*c) || prs_is_underbar(c));
}

t_bool	prs_is_possible_var_name(char *c)
{
	return (ft_isalnum(*c) || prs_is_underbar(c));
}

t_bool	prs_is_end_of_name(char *str)
{
	if (*str && !prs_is_white_space(str) && !prs_is_redir(str) && !prs_is_quote(str))
		return (TRUE);
	return (FALSE);
}
