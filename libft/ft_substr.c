/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:20:11 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:17:33 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	mem_needed(char const *s, unsigned int start, size_t len)
{
	if (!len || start > (ft_strlen(s) - 1))
		return (1);
	else if (ft_strlen(s) - start < len)
		return (ft_strlen(s) - start + 1);
	else
		return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*ptr_substr;

	if (!s)
		return (NULL);
	substr = malloc(mem_needed(s, start, len));
	if (!substr)
		return (NULL);
	ptr_substr = substr;
	while (*s && start--)
		s++;
	while (*s && len)
	{
		*ptr_substr = *s;
		ptr_substr++;
		s++;
		len--;
	}
	*ptr_substr = '\0';
	return (substr);
}
