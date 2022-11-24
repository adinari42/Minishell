/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:11:23 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:16:43 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_spot;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	ft_memcpy(join_spot, s1, ft_strlen(s1));
	len = ft_strlen(s2) + 1;
	ft_strlcpy(join_spot + ft_strlen(s1), s2, len);
	return (join_spot);
}
