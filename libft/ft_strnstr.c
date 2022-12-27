/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:57:07 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:06:51 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*foundptr;
	const char	*needle_start;
	size_t		needle_len;
	size_t		len_remaining;

	if (!(*needle))
		return ((char *) haystack);
	needle_start = (char *) needle;
	while (*haystack && len > 0)
	{
		needle_len = ft_strlen(needle);
		foundptr = (char *) haystack;
		len_remaining = len;
		while (*foundptr++ == *needle++ && len_remaining--)
		{
			needle_len--;
			if (!needle_len || !(*needle))
				return ((char *) haystack);
		}
		needle = needle_start;
		haystack ++;
		len --;
	}
	return (0);
}
