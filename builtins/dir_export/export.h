/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:42 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 18:48:37 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../../libft/libft.h"

//main_filecd
void		stop(char *shell_name);
void		final_print(char **av);
void		distributor(char **av, char **env);

//valid
int			bad_chars(char *arg);
void		validator(char **av);
void		av_remove(char **av, int num);
void		remove_duplicate(char **av);

//utils
int			err_print(char *arg, char *shell_name);
int			word_freer(char **words);
int			env_cmp(char *arg, char *env, char *shell_name);
int			up_strncmp(const char *str1, const char *str2);
int			up_putendl_fd(char *s, int fd);

//srt
int			get_len(char **args);
void		no_args(char **env);
void		env_srt(char **env);
void		env_swap(char **arr_1, char **arr_2);

#endif
