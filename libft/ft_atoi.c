/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:32:13 by slakner           #+#    #+#             */
/*   Updated: 2022/03/26 13:56:45 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(const char *c)
{
	if (*c == ' ' || *c == '\n' || *c == '\t'
		|| *c == '\v' || *c == '\f' || *c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	number;
	int	digit;
	int	i;
	int	positive_negative;

	number = 0;
	positive_negative = 1;
	i = 0;
	while (is_whitespace(str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			positive_negative *= -1;
		str ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		number = number * 10 + digit;
		i++;
	}
	return (number * positive_negative);
}
