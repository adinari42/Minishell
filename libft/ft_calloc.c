/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:39:32 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:09:27 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	memsize;

	memsize = size * count;
	if (size && (memsize / size != count))
		return (NULL);
	mem = malloc(memsize);
	if (!mem)
		return (NULL);
	ft_bzero(mem, memsize);
	return (mem);
}
