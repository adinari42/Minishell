/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:02:54 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:06:04 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	strlen_src;
	size_t	len_dst;

	strlen_src = ft_strlen(src);
	len_dst = 0;
	while (*dst && dstsize > 0)
	{
		dst++;
		len_dst++;
		dstsize--;
	}
	while (*src && dstsize > 1)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize == 1 || *src == 0)
		*dst = '\0';
	return (len_dst + strlen_src);
}
