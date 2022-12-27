/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:18:43 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:16:59 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_charset(char c, const char *charset)
{
	char	*ptr;

	ptr = (char *) charset;
	while (*ptr)
	{
		if (c == *ptr)
			return (1);
		ptr ++;
	}
	return (0);
}

static size_t	find_start(char *ptr, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(ptr) && char_in_charset(ptr[i], set))
		i++;
	return (i);
}

static size_t	find_end(char *ptr, char const *set)
{
	size_t	i;

	i = ft_strlen(ptr) - 1;
	while (i > 0 && char_in_charset(ptr[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s_ptr;
	char	*substr;
	size_t	start_idx;
	size_t	end_idx;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	s_ptr = (char *) s1;
	start_idx = find_start(s_ptr, set);
	end_idx = find_end(s_ptr, set);
	if (start_idx >= ft_strlen(s1))
		return (ft_strdup(""));
	size = (end_idx - start_idx + 2);
	substr = malloc(size);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, &(s1[start_idx]), size);
	return (substr);
}
