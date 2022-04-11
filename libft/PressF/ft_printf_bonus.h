/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:59:36 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/04 00:08:04 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include "libft.h"

# ifndef FLAGS
#  define FLAGS "cs%pdiuxX\0"
# endif

int		ft_printf(const char *inp, ...);
int		filler(unsigned char c, unsigned long i, int num, int base);
char	*dlc_runner(char *cpy, int *d, int *prs, int *padding);
int		shifter(int *d, int cnt);
void	putnbr_base(char d, unsigned long un, int n);

#endif