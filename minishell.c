/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:35:07 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 20:05:14 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readenv(t_list **env, char *path, char *envpath, int envfd)
{
	char	*ret;
	t_bool	pathwas;

	ret = get_next_line(envfd);
	if (ret)
		ft_lstclear(env, &free);
	pathwas = FALSE;
	while (ret)
	{
		ret[ft_strlen(ret) - 1] = '\0';
		if (!ft_strncmp(ret, "PATH=", ft_strlen("PATH=")) && ++pathwas
			&& !ft_strnstr(ret, path, -1))
			ft_lstadd_back(env, ft_lstnew(ft_strjoin(ret, envpath)));
		else
			ft_lstadd_back(env, ft_lstnew(ft_strdup(ret)));
		ret = get_next_line(envfd);
	}
	free(envpath);
	if (!pathwas)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("PATH=", path)));
}

void	handleexeptions(t_fds *fds, t_list **env, char *path, char *prog)
{
	char	*buf;
	char	*pth;

	readenv(env, path, ft_strjoin(":", path), fds->env[0]);
	close(fds->env[0]);
	pth = NULL;
	buf = get_next_line(fds->path[0]);
	while (buf)
	{
		if (pth)
			free(pth);
		pth = buf;
		buf = get_next_line(fds->path[0]);
	}
	if (pth)
		cd(prog, pth, env);
	if (pth)
		free(pth);
	close(fds->path[0]);
	buf = get_next_line(fds->ex[0]);
	if (buf)
	{
		free(buf);
		exit(0);
	}
	close(fds->ex[0]);
}

int	main(int argc, char **argv)
{
	t_head	head;
	int		stat_loc;
	char	*prompt;

	prompt = shellinit(&head.path, &head.prog, *argv, &head.env);
	while (1)
	{
		head.cmd = readline(prompt);
		if (!head.cmd)
			ft_putstr_fd("exit\n", 1);
		if (!head.cmd)
			break ;
		if (!*head.cmd)
			continue ;
		add_history(head.cmd);
		if (!strvalidator(head.prog, head.cmd))
		{
			handlecmd(&head, &stat_loc);
			handleexeptions(&head.fds, &head.env, head.path, head.prog);
		}
		free(head.cmd);
	}
	clear_history();
	free(prompt);
	return (0);
}
