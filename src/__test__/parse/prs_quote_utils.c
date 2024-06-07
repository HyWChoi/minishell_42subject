#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_is_double_quote(char *c)
{
	return (PRS_DOUBLE_QUOTE == *c);
}

t_bool	prs_is_single_quote(char *c)
{
	return (PRS_SINGLE_QUOTE == *c);
}

t_bool	prs_is_quote(char *c)
{
	return (prs_is_double_quote(c) || prs_is_single_quote(c));
}
