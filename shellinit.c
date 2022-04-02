/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:34:31 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 20:17:05 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrlc_handler(int signum)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	rememberpath(char **path, char *argv)
{
	char	*curdir;
	char	*newdir;
	char	*dirpath;

	curdir = getcwd(NULL, 0);
	newdir = curdir;
	if (ft_strchr(argv, '/'))
	{
		dirpath = malloc(sizeof(*dirpath) * (ft_strchr(argv, '/') - argv));
		ft_strlcat(ft_bzero(dirpath, ft_strchr(argv, '/') - argv), argv, ft_strchr(argv, '/') - argv + 1);
		cd(ft_strrchr(argv, '/') + 1, dirpath, NULL);
		free(dirpath);
		newdir = getcwd(NULL, 0);
	}
	*path = ft_strjoin(newdir, "/builtins");
	if (newdir != curdir)
		cd(ft_strrchr(argv, '/') + 1, curdir, NULL);
	if (newdir != curdir)
		free(newdir);
	free(curdir);
}

static void	increaselvl(t_list **env, char *path)
{
	t_list	*crsr;
	char	*buf;

	crsr = *env;
	while (crsr)
	{
		if (ft_strncmp(crsr->content, "SHLVL=", ft_strlen("SHLVL=")))
		{
			crsr = crsr->next;
			continue ;
		}
		buf = ft_itoa(ft_atoi(crsr->content + ft_strlen("SHLVL=")) + 1);
		free(crsr->content);
		crsr->content = ft_strjoin("SHLVL=", buf);
		free(buf);
		return ;
	}
	ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL=1")));
}

char	*shellinit(char **path, char **prog, char *argv, t_list **env)
{
	struct termios	p;
	int				pfd[2];

	tcgetattr(0, &p);
	p.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, 0, &p);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_handler);
	pipe(pfd);
	while (*environ)
	{
		ft_putstr_fd(*environ++, pfd[1]);
		ft_putstr_fd("\n", pfd[1]);
	}
	close(pfd[1]);
	rememberpath(path, argv);
	*env = NULL;
	readenv(env, *path, ft_strjoin(":", *path), pfd[0]);
	increaselvl(env, *path);
	close(pfd[0]);
	*prog = argv;
	if (ft_strrchr(argv, '/'))
		*prog = ft_strrchr(argv, '/') + 1;
	return (ft_strjoin(*prog, "> "));
}
