/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:13:40 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:14:49 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_not_zero(int integer, int fd)
{
	if (integer == 0)
	{
		write (fd, "0", 1);
		return (0);
	}
	return (1);
}

static void	digit_to_char(int integer, char *digits, int pos)
{
	if (integer < 0)
		digits[pos] = '0' + (integer % 10) * -1;
	else
		digits[pos] = '0' + (integer % 10);
}

static void	write_nonzero_int(int integer, int fd)
{
	char	digits[10];
	int		pos;

	pos = 0;
	if (integer < 0)
		write (fd, "-", 1);
	while (integer != 0)
	{
		digit_to_char(integer, digits, pos);
		integer /= 10;
		pos++;
	}
	while (pos > 0)
	{
		pos --;
		write (fd, &digits[pos], 1);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (is_not_zero(nb, fd))
	{
		write_nonzero_int(nb, fd);
	}
}
