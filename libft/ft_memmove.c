/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:06:17 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:14:29 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	else if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i --;
			((char *) dst)[i] = ((char *) src)[i];
		}
	}
	return (dst);
}
