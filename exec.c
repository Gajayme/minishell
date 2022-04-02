/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:04 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/03 01:37:14 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pathdefiner(char *prog, char **env)
{
	char	**path;
	char	*bpath;
	int		acs;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", ft_strlen("PATH=")))
			break ;
	if (!ft_strnstr(env[i], "PATH=", -1))
		return (NULL);
	path = ft_split(env[i] + ft_strlen("PATH="), ':');
	i = arrsize(path);
	while (--i >= 0)
	{
		bpath = ft_strjoin(path[i], prog);
		acs = access_checker(bpath);
		if (!acs && eraser(path))
			return (bpath);
		free(bpath);
		if (acs == -2 && eraser(path))
			return (NULL);
	}
	eraser(path);
	return (NULL);
}

static int	executor(t_cmd *cmd, char **env, char *prog, t_bool isbuiltin)
{
	char	**flags;
	char	*buf;
	char	*path;

	flags = cmdarr(cmd->args, TRUE);
	if (!flags)
		return (error_handler(prog, argcast(cmd->args)->arg, -1));
	if (ft_strchr(flags[0 + isbuiltin], '/'))
	{
		path = flags[isbuiltin];
		flags[isbuiltin] = ft_strrchr(flags[isbuiltin], '/') + 1;
		return (error_handler(prog, path, execve(path, flags, env)));
	}
	buf = ft_strjoin("/", flags[isbuiltin]);
	path = pathdefiner(buf, env);
	free(buf);
	if (!path)
		return (error_handler(prog, flags[isbuiltin], -1));
	return (error_handler(prog, flags[isbuiltin], execve(path, flags, env)));
}

static t_bool	closefds(t_fds *fds, int leftpfd[2])
{
	if (leftpfd && leftpfd[0])
		close(leftpfd[0]);
	if (leftpfd && leftpfd[1])
		close(leftpfd[1]);
	if (fds->envfds)
		close(((int *)ft_lstlast(fds->envfds)->content)[1]);
	return (TRUE);
}

void	envhndlr(t_list *args, t_head *head)
{
	t_list	*qtxt;
	char	*buf;

	if (ft_strncmp(argcast(args)->arg, "export", -1)
		&& ft_strncmp(argcast(args)->arg, "unset", -1))
	{
		ft_lstadd_back(&head->fds.envfds, ft_lstnew(malloc(sizeof(int) * 2)));
		pipe(ft_lstlast(head->fds.envfds)->content);
	}
	while (args)
	{
		if (!ft_strchr(argcast(args)->arg, '$'))
		{
			buf = head->cmd;
			head->cmd = argcast(args)->arg;
			head->isredir = TRUE;
			expandspecialsigns(head, &qtxt);
			head->isredir = FALSE;
			argcast(args)->arg = head->cmd;
			head->cmd = buf;
		}
		args = args->next;
	}
}

int	forker(t_list *curcmd, t_head *head, int rightpfd[2], pid_t *pidsfd)
{
	int		leftpfd[2];
	int		strindx;
	t_bool	isbuiltin;

	ft_bzero(leftpfd, sizeof(*leftpfd) * 2);
	if (getprevstruct(head->pipe, curcmd))
		error_handler(head->prog, NULL, pipe(leftpfd));
	if (getprevstruct(head->pipe, curcmd))
		forker(getprevstruct(head->pipe, curcmd), head, leftpfd, pidsfd);
	strindx = structindex(head->pipe, curcmd);
	envhndlr(cmdcast(curcmd)->args, &head);
	pidsfd[strindx] = error_handler(head->prog, NULL, fork());
	if (pidsfd[strindx] && closefds(&head->fds, leftpfd))
		return (0);
	free(pidsfd);
	if (head->fds.envfds)
		close(((int *)ft_lstlast(head->fds.envfds)->content)[0]);
	rdrhndlr(cmdcast(curcmd), &head->fds, head);
	builtinhndlr(cmdcast(curcmd), head, &isbuiltin);
	mounter(leftpfd, rightpfd, cmdcast(curcmd)->fd, head->prog);
	return (executor(cmdcast(curcmd), cmdarr(head->env, FALSE), head->prog,
			isbuiltin));
}
