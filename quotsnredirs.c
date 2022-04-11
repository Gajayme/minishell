/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotsnredirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:59:23 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 18:50:28 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotedtxt(char *cmd, char *prog, t_list **qtxt)
{
	t_bounds	*qt;
	t_bounds	quots;

	quots.begin = ft_strchr(cmd, '\'');
	if (!quots.begin
		|| (ft_strchr(cmd, '\"') && ft_strchr(cmd, '\"') < quots.begin))
		quots.begin = ft_strchr(cmd, '\"');
	if (!quots.begin)
		return ;
	quots.end = ft_strchr(quots.begin + 1, *quots.begin);
	if (!quots.end)
		parserr(prog, quots.begin + ft_strlen(quots.begin) - 1);
	quotedtxt(quots.end + 1, prog, qtxt);
	if (prog)
		return ;
	qt = malloc(sizeof(*qt));
	qt->begin = quots.begin;
	qt->end = quots.end;
	ft_lstadd_front(qtxt, ft_lstnew(qt));
}

t_bool	outqt(char *str, t_list *qtxt, t_bool strict)
{
	if (!str)
		return (FALSE);
	while (qtxt && boundcast(qtxt)->begin < str)
	{
		if (strict && boundcast(qtxt)->begin < str
			&& str < boundcast(qtxt)->end)
			return (FALSE);
		if (*str != '$'
			&& boundcast(qtxt)->begin < str && str < boundcast(qtxt)->end)
			return (FALSE);
		if (*str == '$' && *boundcast(qtxt)->begin == '\''
			&& boundcast(qtxt)->begin < str && str < boundcast(qtxt)->end)
			return (FALSE);
		qtxt = qtxt->next;
	}
	return (TRUE);
}

static char	*specialhndlr(t_bounds *dlr, t_head *head)
{
	t_bounds	*new;
	t_list		*qtxt;
	char		*cdlr;
	char		**ref;

	qtxt = NULL;
	new = expandspecialsigns(dlr, head, &qtxt);
	if (new == dlr)
		return (txtcopy(dlr, NULL, qtxt));
	cdlr = symbdefiner(dlr, "$*", qtxt);
	if (!istoken(cdlr, "$*") || (*cdlr == '$' && !outqt(cdlr, qtxt, TRUE)))
		return (txtcopy(dlr, NULL, qtxt));
	ref = ft_split(new->begin, ' ');
	if (arrsize(ref) > 1)
		redirerr(head->prog, dlr->begin);
	if (eraser(ref) && qtxt != head->qtxt)
		ft_lstclear(&qtxt, &free);
	cdlr = new->begin;
	free(new);
	return (cdlr);
}

static int	rdr(t_list *redirs, t_bool src, t_head *head)
{
	int			fd;
	t_redir		*redir;

	fd = (!src);
	while (redirs && fd != -1)
	{
		redir = rdrcast(redirs);
		if (redir->src == src && fd && fd != 1)
			close(fd);
		if (redir->src == src && redir->apporstdin && src)
			fd = maninp(redir->florlmt);
		else if (redir->src == src)
		{
			redir->florlmt = specialhndlr(&redir->word, head);
			fd = file_check(redir->florlmt, R_OK * src + W_OK * (!src),
					redir->apporstdin, head->prog);
		}
		redirs = redirs->next;
	}
	return (fd);
}

void	rdrhndlr(t_cmd	*cmd, t_prnths *prnth, t_fds *fds, t_head *head)
{
	if (prnth)
	{
		prnth->fd[0] = rdr(prnth->redirs, TRUE, head);
		prnth->fd[1] = rdr(prnth->redirs, FALSE, head);
		ft_lstclear(&prnth->redirs, &clearredirlst);
		return ;
	}
	cmd->fd[0] = rdr(cmd->redirs, TRUE, head);
	cmd->fd[1] = rdr(cmd->redirs, FALSE, head);
	ft_lstclear(&cmd->redirs, &clearredirlst);
	if (cmd->fd[1] != 1 && ((ft_lstsize(cmd->args) > 1
				&& !ft_strncmp(cmd->args->content, "export", -1))
			|| !ft_strncmp(cmd->args->content, "cd", -1)
			|| !ft_strncmp(cmd->args->content, "exit", -1)))
		close(cmd->fd[1]);
	if (ft_lstsize(cmd->args) > 1
		&& (!ft_strncmp(cmd->args->content, "export", -1)
		|| !ft_strncmp(cmd->args->content, "unset", -1)))
		cmd->fd[1] = ((int *)ft_lstlast(fds->envfds)->content)[1];
	if (!ft_strncmp(cmd->args->content, "cd", -1))
		cmd->fd[1] = fds->path[1];
	if (!ft_strncmp(cmd->args->content, "exit", -1))
		cmd->fd[1] = fds->ex[1];
}
