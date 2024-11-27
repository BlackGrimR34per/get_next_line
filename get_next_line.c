/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:07:27 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/26 19:49:10 by yosherau         ###   ########.fr       */
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

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	output = NULL;
	if (remainder)
	{
		output = handle_remainder(&remainder);
		if (output)
			return (output);
	}
	output = read_into_buffer(output, buffer, fd);
	if (output)
	{
		if (ft_strchr(buffer, NEWLINE))
			remainder = get_remainder(buffer);
	}
	return (output);
}

static char	*read_into_buffer(char *output, char *buffer, int fd)
{
	char	*temp;
	ssize_t	bytes_read;

	if (!output)
	{
		output = malloc(sizeof(char));
		if (!output)
			return (NULL);
		*output = '\0';
	}

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = output;
		output = ft_strappend(output, buffer);
		free(temp);

		if (!output)
			return (NULL);

		if (ft_strchr(buffer, '\n'))
			break ;

		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}

	// If no bytes read and output is empty, free and return NULL
	if (bytes_read <= 0 && (!output || *output == '\0'))
	{
		free(output);
		return (NULL);
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
	char	*ptr;

	if (!*remainder)
		return (NULL);

	ptr = ft_strchr(*remainder, NEWLINE);
	if (ptr)
	{
		// Include newline in the output
		output = malloc((ptr - *remainder) + 2);
		if (!output)
			return (NULL);

		// Copy up to and including newline
		ft_strlcpy(output, *remainder, (ptr - *remainder) + 2);

		// Update remainder
		char *temp = *remainder;
		*remainder = ft_strdup(ptr + 1);
		free(temp);
	}
	else
	{
		// No newline, return entire remainder
		output = *remainder;
		*remainder = NULL;
	}

	return (output);
}
