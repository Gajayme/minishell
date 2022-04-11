/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:04 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 20:03:35 by dcelsa           ###   ########.fr       */
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

	flags = cmdarr(cmd->args);
	if (!flags)
		return (error_handler(prog, cmd->args->content, -1));
	signal(SIGQUIT, SIG_DFL);
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
		return (cmdnotfound(prog, flags[isbuiltin]));
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
	arghndlr(cmdcast(curcmd)->args, &cmdcast(curcmd)->args, head);
	pidsfd[strindx] = error_handler(head->prog, NULL, fork());
	if (pidsfd[strindx] && closefds(&head->fds, leftpfd))
		return (0);
	free(pidsfd);
	if (head->fds.envfds)
		close(((int *)ft_lstlast(head->fds.envfds)->content)[0]);
	rdrhndlr(cmdcast(curcmd), &head->fds, head);
	builtinhndlr(cmdcast(curcmd), head, &isbuiltin);
	mounter(leftpfd, rightpfd, cmdcast(curcmd)->fd, head->prog);
	return (executor(cmdcast(curcmd), cmdarr(head->env), head->prog,
			isbuiltin));
}
