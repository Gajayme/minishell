#include "minishell.h"

static t_bool	filematcher(char *entry, t_list *part, t_list *parts)
{
	if (part == ft_lstlast(parts))
	{
		if (!part->content)
			return (TRUE);
		entry += ft_strlen(entry) - ft_strlen(part->content);
		return (entry >= 0 && !ft_strncmp(entry, part->content, -1));
	}
	if (part != parts && !ft_strnstr(entry, part->content, -1))
		return (FALSE);
	if (part != parts)
		return (filematcher(ft_strnstr(entry, part->content, -1)
			+ ft_strlen(part->content), part->next, parts));
	if (part->content && ft_strncmp(part->content, entry,
			ft_strlen(part->content)))
		return (FALSE);
	if (!filematcher(entry + ft_strlen(part->content),
		part->next, parts))
		return (FALSE);
	return (TRUE);
}

static char *compileentries(t_list **entries, int size)
{
	t_list	*crsr;
	char	*line;
	char	*buf;

	crsr = *entries;
	while (crsr)
	{
		size += ft_strlen(crsr->content);
		crsr = crsr->next;
	}
	line = malloc(sizeof(*line) * (size + ft_lstsize(*entries) - 1));
	buf = line;
	crsr = *entries;
	while (crsr)
	{
		if (buf > line)
			*buf++ = ' ';
		buf += ft_strlcpy(buf, crsr->content, ft_strlen(crsr->content) + 1);
		crsr = crsr->next;
	}
	ft_lstclear(entries, &free);
	return (line);
}

static char *filedef(t_bounds *word, t_list *parts, char *cwd)
{
	struct dirent	*ret;
	t_list			*entries;
	DIR				*dir;
	
	entries = NULL;
	dir = opendir(cwd);
	free(cwd);
	ret = NULL + 1;
	while (ret)
	{
		ret = readdir(dir);
		if (!ret || *ret->d_name == '.'
			|| ((*word->end == '/' && ret->d_type != DT_DIR)
			|| !filematcher(ret->d_name, parts, parts)))
			continue ;
		ft_lstadd_back(&entries, ft_lstnew(slash(word->end,
											ft_strdup(ret->d_name))));
	}
	closedir(dir);
	return (compileentries(&entries, 0));
}

static void partbuilder(t_bounds *word, t_list **parts, t_head *head, t_list *qtxt)
{
	t_bounds	bounds;

	bounds.begin = word->begin;
	bounds.end = symbdefiner(word, "*", qtxt);
	bounds.end -= istoken(bounds.end, "*") + (!*bounds.end);
	if (*bounds.begin != '*')
		ft_lstadd_back(parts, ft_lstnew(txtcopy(&bounds, NULL, qtxt, FALSE)));
	else
		ft_lstadd_back(parts, ft_lstnew(NULL));
	bounds.end += istoken(bounds.end + 1, "*") + (!*(bounds.end + 1));
	if (*bounds.begin == '*')
		bounds.end = bounds.begin;
	while (*bounds.end == '*')
		bounds.end++;
	if ((!*bounds.end || istoken(bounds.end, " <>&|")) && *(bounds.end - 1) == '*')
		ft_lstadd_back(parts, ft_lstnew(NULL));
	if (!*bounds.end || istoken(bounds.end, " <>&|"))
		return ;
	bounds.begin = bounds.end;
	bounds.end = word->end;
	partbuilder(&bounds, parts, head, qtxt);
}

void	wildcardhndlr(char *crsr, t_head *head, t_list **exps, t_list *qtxt)
{
	t_list		*parts;
	t_list		*entries;
	t_bounds	cmd;

	cmd.begin = crsr;
	cmd.end = cmd.begin + ft_strlen(cmd.begin);
	if (*cmd.begin != '*')
		cmd.begin = symbdefiner(&cmd, "*", qtxt);
	if (*cmd.begin != '*')
		return ;
	while (cmd.begin > head->cmd && !istoken(cmd.begin - 1, "&|<> "))
		cmd.begin--;
	cmd.end = symbdefiner(&cmd, "&|<> ", qtxt);
	if (rediravoider(cmd.begin, head->cmd, TRUE))
		wildcardhndlr(cmd.end, head, exps, qtxt);
	if (rediravoider(cmd.begin, head->cmd, TRUE))
		return ;
	parts = NULL;
	partbuilder(&cmd, &parts, head, qtxt);
	ft_lstadd_back(exps, ft_lstnew(malloc(sizeof(t_exp))));
	cmd.end -= !*cmd.end;
	expcast(ft_lstlast(*exps))->val = filedef(&cmd, parts, getcwd(NULL, 0));
	expcast(ft_lstlast(*exps))->sns.begin = cmd.begin;
	expcast(ft_lstlast(*exps))->sns.end = ++cmd.end;
	if (!expcast(ft_lstlast(*exps))->val)
		expcast(ft_lstlast(*exps))->sns.end = cmd.begin;
	ft_lstclear(&parts, &free);
	wildcardhndlr(cmd.end, head, exps, qtxt);
}
