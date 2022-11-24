/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:49:34 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:10:54 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chars_required(int n)
{
	int	chars_required;

	chars_required = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		chars_required += 1;
	}
	if (n < 0)
		chars_required += 1;
	return (chars_required);
}

static void	nonzero_int(char *int_str, int n, int numchars)
{
	int	digit;

	digit = numchars - 1;
	if (n < 0)
		int_str[0] = '-';
	while (n != 0)
	{
		if (n < 0)
			int_str[digit] = n % 10 * -1 + '0';
		else
			int_str[digit] = n % 10 + '0';
		n /= 10;
		digit --;
	}
}

char	*ft_itoa(int n)
{
	char	*int_str;
	int		numchars;

	numchars = chars_required(n);
	int_str = malloc(numchars + 1);
	if (!int_str)
		return (NULL);
	if (!n)
	{
		int_str[0] = '0';
		int_str[1] = '\0';
	}
	else
	{
		nonzero_int(int_str, n, numchars);
		int_str[numchars] = '\0';
	}
	return (int_str);
}
