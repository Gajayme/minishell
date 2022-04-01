#include "minishell.h"

void	quotedtxt(char *cmd, char *prog, t_list **qtxt, t_bool vldmod)
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
	quotedtxt(quots.end + 1, prog, qtxt, vldmod);
	if (vldmod)
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
	t_bounds	new;
	t_list		*qtxt;
	char		*cmd;
	char		**ref;

	cmd = head->cmd;
	head->cmd = dlr->begin;
	head->isredir = TRUE;
	expandspecialsigns(head, &qtxt);
	head->isredir = FALSE;
	new.begin = head->cmd;
	head->cmd = cmd;
	new.end = new.begin + ft_strlen(new.begin) - 1;
	cmd = txtcopy(&new, NULL, qtxt, FALSE);
	free(new.begin);
	new.end = dlr->begin;
	if (!istoken(new.end, "$*"))
		new.end = symbdefiner(dlr, "$*", qtxt);
	new.end -= (!*new.end);
	ref = ft_split(cmd, ' ');
	if (((*new.end == '$' && outqt(new.end, qtxt, TRUE)) || *new.end == '*') && arrsize(ref) > 1)
		redirerr(head->prog, dlr->begin);
	eraser(ref);
	ft_lstclear(&qtxt, &free);
	return (cmd);
}

static int	rdr(t_list *redirs, t_bool src, t_head *head)
{
	int			fd;
	t_redir		*redir;
	t_bounds	file;

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
			file.begin = redir->florlmt;
			file.end = file.begin + ft_strlen(file.begin);
			redir->florlmt = specialhndlr(&file, head);
			fd = file_check(redir->florlmt, R_OK * src + W_OK * (!src),
							redir->apporstdin, head->prog);
		}
		redirs = redirs->next;
	}
	return (fd);
}

void	rdrhndlr(t_cmd	*cmd, t_fds *fds, t_head *head)
{
	char	*ncmd;

	ncmd = argcast(cmd->args)->arg;
	cmd->fd[0] = rdr(cmd->redirs, TRUE, head);
	cmd->fd[1] = rdr(cmd->redirs, FALSE, head);
	if (cmd->fd[1] != 1 && ((ft_lstsize(cmd->args) > 1
		&& !ft_strncmp(ncmd, "export", -1)) || !ft_strncmp(ncmd, "cd", -1)
		|| !ft_strncmp(ncmd, "exit", -1)))
		close(cmd->fd[1]);
	if ((ft_lstsize(cmd->args) > 1 && !ft_strncmp(ncmd, "export", -1))
		|| !ft_strncmp(ncmd, "unset", -1))
		cmd->fd[1] = fds->env[1];
	if (!ft_strncmp(ncmd, "cd", -1))
		cmd->fd[1] = fds->path[1];
	if (!ft_strncmp(ncmd, "exit", -1))
		cmd->fd[1] = fds->ex[1];
	ft_lstclear(&cmd->redirs, &clearredirlst);
}
