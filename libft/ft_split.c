/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 23:36:44 by adinari           #+#    #+#             */
/*   Updated: 2022/04/19 01:23:31 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*str_count returns n number of total strings splitted by c
str_radius returns i the length of the current string to use it in str_fill
str_fill fills s1 with i bits from s + i in s1
free_all frees n strings from the double pointer after failure
*/
static int	str_count(char const *s, char c)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static size_t	str_radius(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	str_fill(char **s1, const char *s, char c)
{
	size_t	j;
	size_t	i;
	size_t	rad;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		rad = str_radius(s + i, c);
		if (rad)
		{
			*(s1 + j) = ft_substr(s + i, 0, rad);
			if (!(*(s1 + j)))
				return (0);
			i = i + rad;
			j++;
		}
	}
	return (1);
}

static void	free_all(char **words, int n)
{
	while (n-- > 0)
		free(words[n]);
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**multistr;
	int		n;

	if (s == NULL)
		return (NULL);
	n = str_count(s, c);
	multistr = (char **)malloc(sizeof(char *) * (n + 1));
	if (!multistr)
		return (NULL);
	if (!str_fill(multistr, s, c))
	{
		free_all(multistr, n);
		return (NULL);
	}
	multistr[n] = NULL;
	return (multistr);
}
