#include "minishell.h"

static t_bool	prnthredirs(char *cmds, char *begin, t_list **redirs, t_bool openprths)
{
	t_redir		*rdr;

	while (cmds < begin && begin < cmds + ft_strlen(cmds)
		&& !istoken(begin, STPSYMBS))
		begin += (!openprths) - openprths;
	if (!istoken(begin, "<>"))
		return (*begin == '|' && *(begin + (!openprths) - openprths) != '|');
	rdr = malloc(sizeof(*rdr));
	rdr->src = (*begin == '<');
	rdr->apporstdin = (*begin == *(begin + (!openprths) - openprths));
	rdr->word.begin = begin + 1 + (!openprths) * rdr->src;
	while (*rdr->word.begin == ' ')
		rdr->word.begin++;
	rdr->word.end = rdr->word.begin;
	while (!istoken(rdr->word.end + 1, "<> &|()"))
		rdr->word.end++;
	if (openprths)
		ft_lstadd_front(redirs, ft_lstnew(rdr));
	else
		ft_lstadd_back(redirs, ft_lstnew(rdr));
	return (prnthredirs(cmds, begin + ((!openprths) - openprths)
		* (1 + rdr->apporstdin), redirs, openprths));
}

static char	*prnthenddef(t_bounds *cmd, t_list *qtxt)
{
	char		*crsr;
	t_bounds	end;

	end.end = cmd->end;
	end.begin = symbdefiner(cmd, ")", qtxt);
	crsr = symbdefiner(cmd, "(", qtxt);
	while (crsr < end.begin)
	{
		crsr = symbdefiner(cmd, "(", qtxt);
		end.begin = symbdefiner(&end, ")", qtxt);
	}
	cmd->end--;
	return (end.begin);
}

void	prnthsfiller(char *cmds, t_bounds cmd, t_list **prnthslst, t_list *qtxt)
{
	t_prnths	*prnths;

	if (*cmd.begin != '(')
		cmd.begin = symbdefiner(&cmd, "(", qtxt);
	if (*cmd.begin != '(')
		return ;
	while (cmd.begin < cmd.end)
	{
		prnths = malloc(sizeof(*prnths));
		prnths->edges.begin = cmd.begin++;
		prnths->edges.end = prnthenddef(&cmd, qtxt);
		prnths->redirs = NULL;
		prnths->ispipe = prnthredirs(cmds, prnths->edges.begin - 1, &prnths->redirs, TRUE);
		prnths->ispipe += prnthredirs(cmds, prnths->edges.end + 1, &prnths->redirs, FALSE);
		prnths->inprt = NULL;
		prnthsfiller(cmds, cmd, &prnths->inprt, qtxt);
		ft_lstadd_back(prnthslst, ft_lstnew(prnths));
		cmd.begin = prnths->edges.end + 1;
	}
}

t_prnths	*inprnths(char *begin, t_list *prnths)
{
	while (prnths)
	{
		if (prnthscast(prnths)->edges.begin < begin && begin < prnthscast(prnths)->edges.end)
			return (prnthscast(prnths));
		prnths = prnths->next;
	}
	return (NULL);
}
