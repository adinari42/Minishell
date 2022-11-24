/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:11:23 by slakner           #+#    #+#             */
<<<<<<< main
/*   Updated: 2022/11/24 19:06:12 by slakner          ###   ########.fr       */
=======
/*   Updated: 2022/04/21 17:16:43 by slakner          ###   ########.fr       */
>>>>>>> added cmd path
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
<<<<<<< main
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
=======
>>>>>>> added cmd path
	size = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, size + 1);
	ft_strlcat(newstr, s2, size + 1);
	return (newstr);
}
