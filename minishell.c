#include "minishell.h"

void	redirerr(char *prog, char *place)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(place, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	exit(1);
}

void	parserr(char *prog, char *place)
{
	ft_putstr_fd(prog, 2);
	if (!istoken(place, STPSYMBS))
		ft_putstr_fd(": parse error near '", 2);
	else
		ft_putstr_fd(": unexpected token '", 2);
	if (*place == '\0')
		ft_putstr_fd("\\n", 2);
	else
		ft_putchar_fd(*place, 2);
	ft_putstr_fd("'\n", 2);
	exit(1);
}

static int	startvalidation(t_head *head)
{
	pid_t	pid;
	int		stat_loc;

	pid = fork();
	if (pid && waitpid(pid, &stat_loc, WUNTRACED))
		return (stat_loc);
	strvalidator(head->prog, head->cmd);
	exit(0);
}

void	rememberpath(char **path, char *argv)
{
	char	*curdir;
	char	*newdir;

	curdir = getcwd(NULL, 0);
	// if (ft_strchr(argv, '/'))
	// 	cd();
	newdir = getcwd(NULL, 0);
	*path = ft_strjoin(newdir, "/builtins");
	// if (ft_strchr(argv, '/'))
	// 	cd(curdir);
	free(curdir);
	free(newdir);
}

void	addpath(t_list **env, char *path)
{
	t_list	*crsr;
	t_bool	pathwas;
	t_bool	lvlwas;

	lvlwas = FALSE;
	pathwas = FALSE;
	crsr = *env;
	while (crsr)
	{
		if (!ft_strncmp("SHLVL=", crsr->content, -1))
			lvlwas++;
		if (!ft_strncmp("PATH=", crsr->content, -1))
			pathwas++;
		crsr = crsr->next;
	}
	if (!lvlwas)
		ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL=1")));
	if (!pathwas)
		ft_lstadd_back(env, ft_lstnew(path));
}

void	readenv(t_list **env, char *path, char *envpath, int envfd)
{
	char	*ret;
	char	*buf;

	ret = get_next_line(envfd);
	if (ret)
		ft_lstclear(env, &free);
	while (ret)
	{
		ret[ft_strlen(ret) - 1] = '\0';
		if (!ft_strncmp(ret, "SHLVL=", ft_strlen("SHLVL=")))
		{
			buf = ft_itoa(ft_atoi(ret + ft_strlen("SHLVL=")) + 1);
			ft_lstadd_back(env, ft_lstnew(ft_strjoin("SHLVL=", buf)));
			free(buf);
		}
		else if (!ft_strncmp(ret, "PATH=", ft_strlen("PATH="))
			&& !ft_strnstr(ret, path, -1))
			ft_lstadd_back(env, ft_lstnew(ft_strjoin(ret, envpath)));
		else
			ft_lstadd_back(env, ft_lstnew(ft_strdup(ret)));
		ret = get_next_line(envfd);
	}
	free(envpath);
	addpath(env, path);
}

void	handleexeptions(t_fds *fds, t_list **env, char *path)
{
	char	*buf;

	readenv(env, path, ft_strjoin(":", path), fds->env[0]);
	close(fds->env[0]);
	buf = get_next_line(fds->path[0]);
	// if (buf)
		// cd(buf);
	if (buf)
		free(buf);
	close(fds->path[0]);
	buf = get_next_line(fds->ex[0]);
	if (buf)
	{
		free(buf);
		exit(0);
	}
}

void	ctrlc_handler(int signum)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
	*env = NULL;
	rememberpath(path, argv);
	readenv(env, *path, ft_strjoin(":", *path), pfd[0]);
	close(pfd[0]);
	*prog = argv;
	if (ft_strrchr(argv, '/'))
		*prog = ft_strrchr(argv, '/') + 1;
	return (ft_strjoin(*prog, "> "));
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
		add_history(head.cmd);
		if (!head.cmd)
			ft_putstr_fd("exit\n", 1);
		if (!head.cmd)
			break ;
		if (!*head.cmd)
			continue ;
		if (!startvalidation(&head))
		{
			handlecmd(&head, &stat_loc);
			handleexeptions(&head.fds, &head.env, head.path);
		}
		free(head.cmd);
	}
	clear_history();
	free(prompt);
	return (0);
}
