/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:08:37 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/01 20:03:59 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <sys/signal.h>
# include "libft.h"
# include "get_next_line.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef SYMBS
#  define SYMBS "&|"
# endif

# ifndef STPSYMBS
#  define STPSYMBS "<>&|"
# endif

# ifndef SIG
#  define SIG 0
# endif

extern int		errno;
extern char		**environ;

typedef int				t_bool;
typedef unsigned int	t_ui;

typedef struct s_dir {
	char			*cwd;
	DIR				*dir;
	struct dirent	*ret;
}	t_dir;

typedef struct s_bounds {
	char			*begin;
	char			*end;
}	t_bounds;

typedef struct s_redir {
	char	*florlmt;
	t_bool	src;
	t_bool	apporstdin;
}	t_redir;

typedef struct s_bracket {
	t_bounds	bounds;
	t_list		*redirs;
	int			fd[2];
	t_bool		ispipe;
}	t_bracket;

typedef struct s_arg
{
	char		*word;
	char		*arg;
}	t_arg;

typedef struct s_cmd {
	t_list		*args;
	t_list		*redirs;
	int			fd[2];
	char		lprior;
	t_bool		ispipe;
}	t_cmd;

typedef struct s_fds {
	int	env[2];
	int	path[2];
	int	ex[2];
}	t_fds;

typedef struct s_exp {
	t_bounds	sns;
	char		*val;
}	t_exp;

typedef struct s_head {
	char	*cmd;
	char	*prog;
	char	*path;
	t_bool	isredir;
	t_list	*env;
	t_list	*pipe;
	t_fds	fds;
	int		referr;
}	t_head;

int			access_checker(char *path);
int			arrsize(char **argv);
t_arg		*argcast(t_list *lst);
t_bounds	*boundcast(t_list *lst);
void		builtinhndlr(t_cmd *cmd, t_fds *fds, t_list *env);
void		clearcmdlst(void *content);
void		clearexp(void *content);
void		clearredirlst(void *content);
char		**cmdarr(t_list *args, t_bool itargs);
t_cmd		*cmdcast(t_list *lst);
char		*dlrhndlr(char *begin, t_head *head, t_list **exps, t_list *qtxt);
int			eraser(char **p);
int			error_handler(char *prog, char *place, int funcres);
void		expandspecialsigns(t_head *head, t_list **qtxt);
t_exp		*expcast(t_list *lst);
int			file_check(char *file, int mod, t_bool app, char *prog);
char		*findenv(char *name, int size, t_head *head, t_bool quoted);
int			forker(t_list *curcmd, t_head *head, int rightpfd[2], pid_t *pidsfd);
t_list		*getprevstruct(t_list *begin, t_list *crnt);
void		handlecmd(t_head *head, int *stat_loc);
t_bool		istoken(char *str, char *tokens);
t_list		*lstcast(t_list *lst);
int			maninp(char *limiter);
void		mounter(int leftpfd[2], int rightpfd[2], int fd[2], char *prog);
t_bool		outqt(char *str, t_list *qtxt, t_bool strict);
void		parser(t_head *head, t_list **cmdlst);
void		parserr(char *prog, char *place);
int			pipehndlr(t_head *head, t_list **crsr);
t_bool		rediravoider(char *crsr, char *cmd, t_bool forwld);
void		redirerr(char *prog, char *place);
t_redir		*rdrcast(t_list *lst);
void		rdrhndlr(t_cmd	*cmd, t_fds *fds, t_head *head);
char		*slash(char *end, char *home);
void		strvalidator(char *prog, char *cmds);
int			structindex(t_list *begin, t_list *curcmd);
char		*symbdefiner(t_bounds *cmd, char *s, t_list *qtxt);
char		*txtcopy(t_bounds *bounds, t_list **args, t_list *qtxt, t_bool skipqts);
void		quotedtxt(char *cmd, char *prog, t_list **qtxt, t_bool vldmod);
void		wildcardhndlr(char *crsr, t_head *head, t_list **exps, t_list *qtxt);

#endif
