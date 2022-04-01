/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:42 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 16:05:27 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../../libft/libft.h"

//struct
typedef struct s_addlist
{
	char				*line;
	int					add_flag;
	struct s_addlist	*next;
}				t_addlist;

//main_file
void		no_args(char **env);
void		distributor(char **av, char **env, t_addlist **list);

//acess
int			path_freer(char **d_path, char *cmd);
char		*path_parse(char **env, char *cmd);
char		*cmd_checker(char **env, char *cmd);

//changers
void		add_one(char *arg, char **env);
char		**add_to_env(t_addlist *list, char **env);
void		add_to_list(char *arg, t_addlist **export);
void		change_one(char *arg, char **env, t_addlist **list);
void		change_or_new(char *arg, char **env, t_addlist **list);

//utils
int			get_len(char **args);
int			env_cmp(char *arg, char *env, t_addlist *list);

//exit
void		err_print(char *arg, int flag, t_addlist *list);
void		freer(t_addlist *list, int flag);
char		*wrapper(char *funk, t_addlist *list);

//lib_utils
int			up_lstsize(t_addlist *lst);
int			up_strncmp(const char *str1, const char *str2);
void		up_lstadd_front(t_addlist **lst, t_addlist *new);
t_addlist	*up_lstnew(char *line, int flag, t_addlist *list);

#endif
