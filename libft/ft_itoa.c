/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:42:35 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 23:32:08 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
**int_len sets length of n to 1 if it's equal to 0 or negative for
extra sign adress.
and keeps dividing by 10 to count number of digits in n.
**true_sign insures that the sign of n remains after multp or div.
**allocating i + 1 for
*/
static int	int_len(long int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long int	true_sign(long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*charstr;
	int		sign;

	i = int_len(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	charstr = (char *)malloc(sizeof(char) * i + 1);
	if (!charstr)
		return (0);
	charstr[i] = '\0';
	i--;
	while (i >= 0)
	{
		charstr[i] = true_sign(n % 10) + '0';
		n = true_sign(n / 10);
		i--;
	}
	if (sign == -1)
		charstr[0] = '-';
	return (charstr);
}
