/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:35:07 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/04 00:07:47 by dcelsa           ###   ########.fr       */
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
		free(ret);
		ret = get_next_line(envfd);
	}
	free(envpath);
	if (!pathwas)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("PATH=", path)));
	close(envfd);
}

void	mainproccd(int pthfd, char *prog, t_list **env)
{
	char	*pth;
	char	*buf;

	pth = NULL;
	buf = get_next_line(pthfd);
	while (buf)
	{
		if (pth)
			free(pth);
		pth = buf;
		pth[ft_strlen(pth) - 1] = '\0';
		buf = get_next_line(pthfd);
	}
	if (pth)
		cd(prog, pth, env);
	if (pth)
		free(pth);
	close(pthfd);
}

void	handleexeptions(t_head *head)
{
	char	*buf;

	readenv(&head->env, head->path, ft_strjoin(":", head->path), head->fds.env[0]);
	mainproccd(head->fds.path[0], head->prog, &head->env);
	buf = get_next_line(head->fds.issig[0]);
	while (buf)
	{
		head->issig = ft_atoi(buf);
		free(buf);
		buf = get_next_line(head->fds.issig[0]);
		head->referr = ft_atoi(buf);
		free(buf);
		buf = get_next_line(head->fds.issig[0]);
	}
	close(head->fds.issig[0]);
	buf = get_next_line(head->fds.ex[0]);
	if (buf)
	{
		free(buf);
		exit(ft_atoi(buf));
	}
	close(head->fds.ex[0]);
}

int	main(int argc, char **argv)
{
	t_head	head;
	char	*prompt;

	(void)argc;
	prompt = shellinit(&head, *argv);
	while (1)
	{
		signal(SIGINT, &emptyintsig);
		head.cmd = readline(prompt);
		signal(SIGINT, &intsig);
		if (!head.cmd)
			ft_putendl_fd("exit", 1);
		if (!head.cmd)
			break ;
		if (*head.cmd)
			add_history(head.cmd);
		if (!strvalidator(head.prog, head.cmd))
		{
			handlecmd(&head, &head.referr);
			handleexeptions(&head);
		}
		free(head.cmd);
	}
	exit(0);
}
