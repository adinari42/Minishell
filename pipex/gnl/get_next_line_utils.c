/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:08:55 by adinari           #+#    #+#             */
/*   Updated: 2022/10/14 21:16:36 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlenn(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlenn(src);
	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

char	*ft_strjoinn(char *str1, char *str2)
{
	size_t	index;
	size_t	count;
	char	*result;

	if (!str1)
	{
		str1 = (char *)malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	if (!str1 || !str2)
		return (NULL);
	result = malloc ((ft_strlenn(str1) + ft_strlenn(str2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	index = -1;
	count = 0;
	if (str1)
		while (str1[++index] != '\0')
			result[index] = str1[index];
	while (str2[count] != '\0')
		result[index++] = str2[count++];
	result[ft_strlenn(str1) + ft_strlenn(str2)] = '\0';
	free(str1);
	return (result);
}

char	*ft_strchrr(char *s, int n)
{
	int	index;

	index = 0;
	if (!s)
		return (0);
	if (n == '\0')
		return ((char *)&s[ft_strlenn(s)]);
	while (s[index] != '\0')
	{
		if (s[index] == (char)n)
			return ((char *)&s[index]);
		index++;
	}
	return (0);
}
