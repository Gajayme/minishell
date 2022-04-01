/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:26:25 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:35:01 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<stdlib.h>
# include<unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30000	
# endif

# define INIT_BUF_SIZE 512

char	*get_next_line(int fd);
char	*remal(char *str, char *buf, size_t len);
void	*erase(void *p1, void **p2);
void	memshift(char *buf, size_t anchor);

#endif