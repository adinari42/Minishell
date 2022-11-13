/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:58:14 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:14:18 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_byte;
	char	*src_byte;

	dst_byte = (char *) dst;
	src_byte = (char *) src;
	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		dst_byte[i] = src_byte[i];
		i++;
	}
	return (dst);
}
