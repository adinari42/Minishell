/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:10:35 by adinari           #+#    #+#             */
/*   Updated: 2022/04/20 05:41:05 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//memcpy don't accept overlapping, memove allows overlapping.
//starting from the end "n" and back to position 0 to not cause overlap
//upon collission/overlap , return dst
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = n;
	while (i-- > 0)
	{
		if (dst + i == src + i)
			return (dst);
		else
			ft_memmove(dst + i, src + i, 1);
	}
	return (dst);
}
