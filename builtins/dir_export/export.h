/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:59:42 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 18:25:00 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../../libft/libft.h"

//main_file
void		stop(char *shell_name);
void		final_print(char **av);
void		distributor(char **av, char **env);

//valid
int			bad_chars(char *arg);
void		validator(char **av);
void		av_remove(char **av, int num);

//utils
int			err_print(char *arg, char *shell_name);
int			word_freer(char **words);
int			env_cmp(char *arg, char *env, char *shell_name);
int			up_strncmp(const char *str1, const char *str2);

//srt
int			get_len(char **args);
void		no_args(char **env);
void		env_srt(char **env);
void		env_swap(char **arr_1, char **arr_2);

#endif
