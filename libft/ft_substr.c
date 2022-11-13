/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:13:07 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 01:05:45 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
**line20: protection against NULL input
**l23: if given empty string for start
duplicates empty string and returns pointer to it
**l27: reduces len to the max that can be taken in that case
**l33: uses strlcpy to copy len + 1 bytes from s + start
and ensures NUL termination
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	l1;
	unsigned int	l2;

	if (!s)
		return (NULL);
	l1 = ft_strlen(s);
	l2 = ft_strlen(s + start);
	if (l1 < start)
		return (ft_strdup(""));
	if (l2 < len)
		len = ft_strlen(s + start);
	sub_str = malloc(len + 1);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}
