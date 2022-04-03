/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:54:52 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/03 20:19:38 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

//LIBS
# include <stdio.h>
# include <errno.h>
# include "../../libft/libft.h"

//main
void	stop(char *shell_name);
int		err_print(char *arg, char *shall_name);
void	distributor(char **av, char **env);

//utils
int		bad_chars(char *arg);
void	validator(char **av);
void	av_remove(char **av, int num);
int		env_cmp(char *arg, char *env, char *shell_name);
int		up_strncmp(const char *str1, const char *str2);

#endif
