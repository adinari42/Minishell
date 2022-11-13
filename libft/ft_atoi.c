/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:13:17 by adinari           #+#    #+#             */
/*   Updated: 2022/04/20 01:29:53 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*skips spaces using line 28 loop, considers '-' sign, increments i
check individual char of str is number (ft_isdigit) 
check ascii of characters and does -48 for conversion (- '0')
multiplies by 10 to push the current integer to left
checks if current val is under or above max long min long int
*/
int	ft_atoi(const char *str)
{
	long	val;
	int		sign;
	int		i;

	val = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		val = (val * 10) + (str[i++] - '0');
		if (val > 2147483647 && sign == 1)
			return (-1);
		if (val > 2147483648 && sign == -1)
			return (0);
	}
	return (val * sign);
}
