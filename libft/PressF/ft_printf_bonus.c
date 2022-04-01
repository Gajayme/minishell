/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:59:32 by dcelsa            #+#    #+#             */
/*   Updated: 2022/03/04 17:59:33 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "libft.h"

static int	num_printer(int *d, unsigned long un, int num, int count)
{
	int	i;
	int	n;

	n = count;
	if (d[1] != '-' && (d[1] != '0' || d[3]))
		count += shifter(d, count + 2 * (d[2] == '#' || d[4] == 'p'));
	if (((d[4] == 'x' && d[2] == '#' && un) || d[4] == 'p')
		&& ++count && ++count)
		ft_putstr_fd("0x", 1);
	if (d[4] == 'X' && d[2] == '#' && un && ++count && ++count)
		ft_putstr_fd("0X", 1);
	if ((d[4] == 'd' || d[4] == 'i') && d[0] && num >= 0 && ++count)
		ft_putchar_fd(d[0], 1);
	if ((d[4] == 'd' || d[4] == 'i') && num < 0)
		ft_putchar_fd('-', 1);
	i = -1;
	if (d[1] != '-' && d[1] == '0' && !d[3])
		count += shifter(d, count);
	while (d[3] && ++i < d[5] - n && ++count)
		ft_putchar_fd('0', 1);
	d[5] -= num < 0;
	if (!(d[3] && !d[5] && !un && !num))
		putnbr_base(d[4], un, num);
	return (count);
}

static int	num_handler(int *d, int num, unsigned int uni, unsigned long unl)
{
	int	count;

	if (d[4] == 'i' || d[4] == 'd' || d[4] == 'u')
		count = filler(0, uni, num, 10) + 1 * (num < 0);
	if (d[4] == 'x' || d[4] == 'X' || d[4] == 'p')
		count = filler(0, uni + unl, 0, 16);
	if (d[3] && d[5] <= 0 && !num && !uni && !unl)
		count = 0;
	if (num < 0)
		d[5]++;
	count = num_printer(d, uni + unl, num, count);
	if (d[1] == '-' && ((num < 0 && d[3] && ++d[5]) || 1))
		count += shifter(d, count);
	return (count);
}

static int	char_handler(int *d, char c, char *s)
{
	int	prs;
	int	count;

	if (d[4] == 's' && !s)
		return (char_handler(d, 0, "(null)"));
	count = ft_strlen(s);
	count = count * (!d[3] || d[5] > count) + d[5] * (d[3] && d[5] <= count);
	count += d[4] != 's';
	if (d[1] != '-')
		count += shifter(d, count);
	if (c)
		ft_putchar_fd(c, 1);
	if (d[4] == 'c' && !c)
		ft_putchar_fd('\x00', 1);
	prs = 0;
	while (s && *s && (!d[3] || (d[3] && prs++ < d[5])))
		ft_putchar_fd(*s++, 1);
	if (d[1] == '-')
		count += shifter(d, count);
	return (count);
}

static char	*spec_det(char *inp, va_list *args, int *p)
{
	int	d[7];
	int	i;

	i = 7;
	while (i--)
		d[i] = 0;
	inp = dlc_runner(inp + 1, d, &d[5], &d[6]);
	if ((d[4] == 'd' || d[4] == 'i') && inp++)
		*p += num_handler(d, va_arg(*args, int), 0, 0);
	if ((d[4] == 'u' || d[4] == 'x' || d[4] == 'X') && inp++)
		*p += num_handler(d, 0, va_arg(*args, unsigned int), 0);
	if (d[4] == 'p' && inp++)
		*p += num_handler(d, 0, 0, va_arg(*args, unsigned long));
	if (d[4] == 's' && inp++)
		*p += char_handler(d, 0, va_arg(*args, char *));
	if (d[4] == 'c' && inp++)
		*p += char_handler(d, va_arg(*args, int), NULL);
	if (d[4] == '%' || d[4] == 1)
		*p += char_handler(d, *inp++, NULL);
	return (inp);
}	

int	ft_printf(const char *inp, ...)
{
	va_list		args;
	char		*pup;
	int			printed;

	pup = (char *) inp;
	if (!pup)
		return (0);
	va_start(args, inp);
	printed = 0;
	while (*pup)
	{
		if (*pup == '%')
			pup = spec_det(pup, &args, &printed);
		else if (++pup && ++printed)
			ft_putchar_fd(*(pup - 1), 1);
	}
	va_end(args);
	return (printed);
}
