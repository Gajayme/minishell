#include "minishell.h"

static void	redirvalidator(t_bounds *bounds, t_list *qtxt, char *prog)
{
	t_bounds	crsr;

	crsr.begin = bounds->begin;
	crsr.end = bounds->end;
	if (!istoken(crsr.begin, "<>"))
		crsr.begin = symbdefiner(&crsr, "<>", qtxt);
	while (crsr.begin < bounds->end)
	{
		if (istoken(++crsr.begin, "<>"))
			crsr.begin++;
		while (*crsr.begin && !istoken(crsr.begin, " <>&|"))
			crsr.begin++;
		crsr.begin -= istoken(crsr.begin, "<>");
		if (istoken(crsr.begin, "<>|&") || *crsr.begin == '*')
			parserr(prog, crsr.begin);
		crsr.begin = symbdefiner(&crsr, "<>", qtxt);
	}
}

static void	dlrvalidator(char *cmds, char *prog, t_list *qtxt)
{
	t_bounds	bounds;

	bounds.begin = cmds;
	bounds.end = cmds + ft_strlen(cmds);
	if (*bounds.begin != '$')
		bounds.begin = symbdefiner(&bounds, "$", qtxt);
	while (bounds.begin < bounds.end)
	{
		if (!ft_isalpha(*(++bounds.begin)) && !istoken(bounds.begin, " '\"?"))
			parserr(prog, bounds.begin);
		bounds.begin = symbdefiner(&bounds, "$", qtxt);
	}
}

static void	checkbounds(t_bounds *crsr, char *prog)
{
	char	*cursor;

	if (crsr->end - crsr->begin < 2 && istoken(crsr->begin, "|&<>"))
		parserr(prog, crsr->end);
	if ((*crsr->end == '&' && *(crsr->end + 1) != '&')
		|| (*crsr->end == '|' && *(crsr->end + 1) == '&'))
		parserr(prog, crsr->end);
	cursor = crsr->begin + 1;
	while (cursor < crsr->end && *cursor == ' ')
		cursor++;
	if (cursor < crsr->end)
		return ;
	parserr(prog, crsr->end);
}

void	strvalidator(char *prog, char *cmds)
{
	t_bounds	crsr;
	t_list		*qtxt;

	qtxt = NULL;
	quotedtxt(cmds, prog, &qtxt, TRUE);
	dlrvalidator(cmds, prog, qtxt);
	crsr.begin = cmds;
	while (crsr.begin < cmds + ft_strlen(cmds))
	{
		crsr.end = crsr.begin + ft_strlen(crsr.begin);
		crsr.end = symbdefiner(&crsr, SYMBS, qtxt);
		checkbounds(&crsr, prog);
		redirvalidator(&crsr, qtxt, prog);
		crsr.begin = crsr.end + (*crsr.end == *(crsr.end + 1));
	}
}
