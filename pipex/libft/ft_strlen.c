/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:16:28 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 00:43:21 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*counts number of characters before NUL termination*/
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
