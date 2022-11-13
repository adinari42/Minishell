/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:31:38 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:06:25 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	idx;

	if (!s || !f)
		return (NULL);
	newstr = malloc(ft_strlen(s) + 1);
	if (!newstr)
		return (NULL);
	idx = 0;
	while (s[idx])
	{
		newstr[idx] = f(idx, s[idx]);
		idx++;
	}
	newstr[idx] = '\0';
	return (newstr);
}
