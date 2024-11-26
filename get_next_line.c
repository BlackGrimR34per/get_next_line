/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:07:27 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/26 15:58:37 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char	*read_into_buffer(char *output, char *buffer, int fd);
static char	*handle_remainder(char **remainder);
static char	*get_remainder(char *buffer);

char	*get_next_line(int fd)
{
	char		*output;
	char		buffer[BUFFER_SIZE + 1];
	static char	*remainder;

	if (BUFFER_SIZE <= 0 || fd <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	output = NULL;
	if (remainder)
		output = handle_remainder(&remainder);
	output = read_into_buffer(output, buffer, fd);
	if (ft_strchr(buffer, NEWLINE))
		remainder = get_remainder(buffer);
	return (output);
}

static char	*read_into_buffer(char *output, char *buffer, int fd)
{
	char	*temp;
	size_t	bytes_read;

	// Must find a condition that solves this issue of forever looping
	if (output == NULL)
	{
		output = malloc(sizeof(char));
		*output = '\0';
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = output;
		output = ft_strappend(output, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, sizeof(*buffer));
	}
	return (output);
}

static char	*get_remainder(char *buffer)
{
	char	*output;
	char	*ptr;

	ptr = ft_strchr(buffer, NEWLINE);
	if (!ptr || *(ptr + 1) == '\0')
		return (NULL);
	output = ft_strdup(ptr + 1);
	if (!output)
		return (NULL);
	return (output);
}

static char	*handle_remainder(char **remainder)
{
	char	*output;
	char	*temp;
	char	*ptr;

	output = malloc(sizeof(char));
	temp = output;
	*output = '\0';
	output = ft_strappend(output, *remainder);
	ptr = ft_strchr(*remainder, NEWLINE);
	if (ptr)
		ptr += 1;
	// Line below fixes mem leaks OwO
	free(*remainder);
	*remainder = ft_strdup(ptr);
	free(temp);
	return (output);
}
