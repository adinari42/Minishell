/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:31:13 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:08:40 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *) s;
	while (*ptr)
		ptr ++;
	if (!c)
		return (ptr);
	while (ptr != s)
	{
		ptr --;
		if (*ptr == (char) c)
			return (ptr);
	}
	return (NULL);
}
