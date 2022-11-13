/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:11:27 by slakner           #+#    #+#             */
/*   Updated: 2022/04/21 17:15:00 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(char *str, char c)
{
	char	*ptr;
	int		ctr;

	ctr = 0;
	ptr = str;
	while (*ptr)
	{
		while (c != *ptr && *ptr)
			ptr ++;
		ctr ++;
		while (c == *ptr && *ptr && c)
			ptr ++;
	}
	return (ctr);
}

static char	**fill_array(char **str_array, char *str, char c, char *wordptr)
{
	int	i;

	i = 0;
	while (*str)
	{
		str ++;
		if (c == *str || !*str)
		{
			str_array[i] = malloc(sizeof(char) * ((str - wordptr) + 1));
			if (str_array[i])
				ft_strlcpy(str_array[i], wordptr, (str - wordptr + 1));
			else
			{
				while (i--)
					free(str_array[i]);
				return (NULL);
			}
			i ++;
			while (*str == c && c)
				str ++;
			wordptr = str;
		}
	}
	str_array[i] = NULL;
	return (str_array);
}

static char	**nullbyte_separator(const char *s)
{
	char	**str_array;

	str_array = malloc(2 * sizeof(char *));
	if (!str_array)
		return (NULL);
	str_array[0] = ft_strdup(s);
	if (!str_array[0])
	{
		free(str_array);
		return (NULL);
	}
	str_array[1] = NULL;
	return (str_array);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	char	*wordptr;
	char	*str;
	char	charstr[2];

	str_array = NULL;
	if (!s)
		return (NULL);
	else if (!c && *s)
		return (nullbyte_separator(s));
	charstr[0] = c;
	charstr[1] = '\0';
	str = ft_strtrim(s, charstr);
	if (!str)
		return (NULL);
	wordptr = str;
	str_array = malloc(sizeof (char *) * (count_strings(str, c) + 1));
	if (str_array)
		str_array = fill_array(str_array, str, c, wordptr);
	free(str);
	return (str_array);
}
