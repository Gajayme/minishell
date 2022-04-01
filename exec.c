/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:04 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/01 18:44:59 by dcelsa           ###   ########.fr       */
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

static int	executor(t_cmd *cmd, char **env, char *prog)
{
	char	**flags;
	char	*buf;
	char	*path;

	flags = cmdarr(cmd->args, TRUE);
	if (!flags)
		return (error_handler(prog, argcast(cmd->args)->arg, -1));
	if (ft_strchr(flags[0], '/'))
	{
		path = flags[0];
		flags[0] = ft_strrchr(flags[0], '/') + 1;
		return (error_handler(prog, path, execve(path, flags, env)));
	}
	buf = ft_strjoin("/", flags[0]);
	path = pathdefiner(buf, env);
	free(buf);
	if (!path)
		return (error_handler(prog, flags[0], -1));
	return (error_handler(prog, flags[0], execve(path, flags, env)));
}

static t_bool	closefds(t_fds *fds, int leftpfd[2])
{
	if (leftpfd && leftpfd[0])
		close(leftpfd[0]);
	if (leftpfd && leftpfd[1])
		close(leftpfd[1]);
	close(fds->env[1]);
	close(fds->ex[1]);
	close(fds->path[1]);
	return (TRUE);
}

void	builtinhndlr(t_cmd *cmd, t_fds *fds, t_list *env)
{
	if (!cmd->ispipe && !ft_strncmp(argcast(cmd->args)->arg, "exit", -1))
		ft_putstr_fd("1", cmd->fd[1]);
	if (!cmd->ispipe && !ft_strncmp(argcast(cmd->args)->arg, "cd", -1))
	{
		if (ft_lstsize(cmd->args) > 1)
			ft_putstr_fd(argcast(cmd->args->next)->arg, cmd->fd[1]);
		if (ft_lstsize(cmd->args) > 1)
			return ;
		while (env && ft_strncmp(env->content, "HOME=", ft_strlen("HOME=")))
			env = env->next;
		if (env && !ft_strncmp(env->content, "HOME=", ft_strlen("HOME=")))
			ft_putstr_fd(env->content + ft_strlen("HOME="), cmd->fd[1]);
	}
	if (!cmd->ispipe)
		return ;
	if ((!ft_strncmp(argcast(cmd->args)->arg, "export", -1)
		&& ft_lstsize(cmd->args) > 1)
		|| !ft_strncmp(argcast(cmd->args)->arg, "unset", -1))
		close(cmd->fd[1]);
	if (!ft_strncmp(argcast(cmd->args)->arg, "cd", -1)
		|| !ft_strncmp(argcast(cmd->args)->arg, "exit", -1))
		close(cmd->fd[1]);
}

int	forker(t_list *curcmd, t_head *head, int rightpfd[2], pid_t *pidsfd)
{
	int		leftpfd[2];
	int		fd[2];
	int		strindx;

	if (!curcmd)
		return (0);
	ft_bzero(leftpfd, sizeof(*leftpfd) * 2);
	if (getprevstruct(head->pipe, curcmd))
		error_handler(head->prog, NULL, pipe(leftpfd));
	forker(getprevstruct(head->pipe, curcmd), head, leftpfd, pidsfd);
	strindx = structindex(head->pipe, curcmd);
	pidsfd[strindx] = error_handler(head->prog, NULL, fork());
	if (pidsfd[strindx] && closefds(&head->fds, leftpfd))
		return (0);
	free(pidsfd);
	rdrhndlr(cmdcast(curcmd), &head->fds, head);
	fd[0] = cmdcast(curcmd)->fd[0];
	fd[1] = cmdcast(curcmd)->fd[1];
	// builtinhndlr(cmdcast(curcmd), &head->fds, head->env);
	mounter(leftpfd, rightpfd, fd, head->prog);
	return (executor(cmdcast(curcmd), cmdarr(head->env, FALSE), head->prog));
}
