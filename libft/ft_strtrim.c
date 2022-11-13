/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:50:19 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 01:13:20 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_index(char const *s, char const *set)
{
	int		k;
	size_t	i;

	i = 0;
	while (s[i])
	{
		k = 0;
		while (ft_strchr(s + i, set[k]) != s + i && k < ft_strlen(set))
			k++;
		if (k >= ft_strlen(set))
			break ;
		if (ft_strchr(s + i, set[k]) == s + i)
			i++;
	}
	return (i);
}

static int	end_index(char const *s, char const *set)
{
	int		k;
	size_t	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		k = 0;
		while (ft_strchr(s + i, set[k]) != s + i && k < ft_strlen(set))
			k++;
		if (k >= ft_strlen(set))
			break ;
		if (ft_strchr(s + i, set[k]) == s + i)
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{	
	char	*s1_trim;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i = (int)start_index(s1, set);
	j = (int)end_index(s1, set) + 1;
	if (i >= j)
		return (ft_strdup(""));
	s1_trim = ft_substr(s1, i, j - i);
	if (!s1_trim)
		return (NULL);
	return (s1_trim);
}
