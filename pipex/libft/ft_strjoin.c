/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:30:21 by adinari           #+#    #+#             */
/*   Updated: 2022/10/18 23:08:50 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_spot;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	join_spot = malloc(ft_strlen(s1) + ft_strlen(s2)+1);
	if (!join_spot)
		return (NULL);
	ft_memcpy(join_spot, s1, ft_strlen(s1));
	len = ft_strlen(s2) + 1;
	ft_strlcpy(join_spot + ft_strlen(s1), s2, len);
	return (join_spot);
}
