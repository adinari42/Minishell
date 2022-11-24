/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:32:57 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:06:42 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_u;
	unsigned char	*s2_u;

	s1_u = (unsigned char *) s1;
	s2_u = (unsigned char *) s2;
	i = 0;
	while (i < n && (*s1_u || *s2_u))
	{
		if (*s1_u != *s2_u)
			return ((*s1_u - *s2_u));
		s1_u++;
		s2_u++;
		i++;
	}
	return (0);
}
