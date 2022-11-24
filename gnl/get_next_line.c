/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:54:50 by adinari           #+#    #+#             */
/*   Updated: 2022/10/14 21:16:50 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//update latest line and start position
//generate new line***************
char	*new_bufferstart(char *buffer)
{
	int		i;
	char	*new_buffer;
	int		l;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	l = ft_strlenn(buffer);
	new_buffer = malloc(l - i);
	if (!new_buffer)
		return (NULL);
	i++;
	l++;
	ft_strlcpy(new_buffer, buffer + i, l - i);
	free(buffer);
	return (new_buffer);
}

char	*gener_line(char *buffer)
{
	char	*res_line;
	size_t	i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	res_line = (char *)malloc(i + 2);
	if (!res_line)
		return (NULL);
	ft_strlcpy(res_line, buffer, i + 2);
	return (res_line);
}

char	*init_buffer(int fd, char *orig_buffer)
{
	char	*capsule;
	int		byt_count;

	byt_count = 1;
	capsule = malloc(BUFFER_SIZE + 1);
	if (!capsule)
		return (NULL);
	while (!(ft_strchrr(orig_buffer, '\n')) && byt_count != 0)
	{
		byt_count = read(fd, capsule, BUFFER_SIZE);
		if (byt_count == -1)
		{
			free(capsule);
			return (NULL);
		}
		capsule[byt_count] = '\0';
		orig_buffer = ft_strjoinn(orig_buffer, capsule);
	}
	free(capsule);
	return (orig_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = init_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	result = gener_line(buffer);
	buffer = new_bufferstart(buffer);
	return (result);
}
