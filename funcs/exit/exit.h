/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:34:23 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 20:54:07 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include "../../libft/libft.h"

//main
int				digit_checker(char *arg, char *shell_name, int fd_exit);
int				overflow_checker(char *arg, char *shell_name, int fd_exit);
int				err_printer(char *arg, char *shell_name);
int				ft_exit(char *shell_name, int fd_exit, char **av);

//utils
int				up_putstr_fd(char *s, int fd);
long			up_atoi(const char *str);
unsigned long	unsigned_atoi(const char *str);
int				get_len(char **av);

#endif
