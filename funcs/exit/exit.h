/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:34:23 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 19:52:54 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

//main
int				digit_checker(char *arg, char *shell_name);
int				overflow_checker(char *arg, char *shell_name);
int				err_printer(char *arg, char *shell_name);
int				ft_exit(char *shell_name, char **av);

//utils
int				up_putstr_fd(char *s, int fd);
long			up_atoi(const char *str);
unsigned long	unsigned_atoi(const char *str);
size_t			ft_strlen(const char *str);
int				get_len(char **av);

#endif
