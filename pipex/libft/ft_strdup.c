/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:21:45 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 00:44:23 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*mem_dup;
	size_t	i;

	i = 0;
	mem_dup = malloc(ft_strlen(s1) + 1);
	if (!mem_dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		mem_dup[i] = s1[i];
		i++;
	}
	mem_dup[i] = '\0';
	return (mem_dup);
}
