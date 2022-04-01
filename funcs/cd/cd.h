/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:10:09 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 20:26:50 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "../../libft/libft.h"

//main
int		cd(char *shell_name, char *dirname, t_list **list);
//utils
int		pprrr(char *shell_name, char *arg);
int		find_curdir(char **cur_dir);
int		dir_changer(char *dirname, t_list **list);
int		find_home(char *shell_name, t_list *list, char **home_dir);
//PWD
int		add_pwd(t_list **list);
int		change_pwd(void **content);
int		env_modify_new(t_list **list);
//OLDPWD
int		add_oldpwd(t_list **list, char *old_dir);
int		change_oldpwd(void **content, char *old_dir);
int		env_modify_old(t_list **list, char *old_dir);
//lib_utils
char	*up_strjoin(char const *s1, char *s2);
int		up_putendl_fd(char *s, int fd);

#endif
