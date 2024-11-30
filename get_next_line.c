/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 01:53:40 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/30 20:33:36 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * TODO: Remove stdio
 * TODO: Fix malloc issue due to get_remainder
 */
#include <stdio.h>

static char	*get_remainder(char *buffer);
static char	*read_into_buffer(char *buffer, int fd);
static char	*handle_remainder(char **remainder);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*output;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	output = NULL;
	if (remainder)
	{
		output = handle_remainder(&remainder);
		return (output);
	}
	output = read_into_buffer(buffer, fd);
	remainder = get_remainder(buffer);
	return (output);
}

/**
 * @brief Reads data from a file descriptor and updates the buffer.
 *
 * This function reads data from the given file descriptor `fd` and fills
 * the provided buffer. It also extracts and returns a line from the buffer
 * if available.
 *
 * @param buffer A pointer to the buffer where the read data will be stored.
 *               The buffer must be pre-allocated.
 * @param fd The file descriptor to read data from.
 *
 * @return A pointer to a dynamically allocated string containing the line read
 *         from the buffer, or NULL if an error occurs or no line is available.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned line.
 */
static char	*read_into_buffer(char *buffer, int fd)
{
	size_t	bytes_read;
	char	*output;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	output = NULL;
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = output;
		output = ft_strappend(output, buffer);
		if (temp)
			free(temp);
		if (ft_strchr(buffer, NEWLINE))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (output);
}

/**
 * @brief Reads data from the buffer and updates the remainder.
 *
 * This function reads data from the buffer and finds the occurence of a newline,
 * if found the string following the newline is duplicated and assigned to
 * remainder
 *
 * @param buffer A pointer to the buffer where the read data will be stored.
 *
 * @return A pointer to a dynamically allocated string containing the string
 *         following the newline character
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned line.
 * !What if substr fails?
 */
static char	*get_remainder(char *buffer)
{
	char	*output;
	char	*ptr;

	ptr = ft_strchr(buffer, NEWLINE);
	if (!ptr || !*(ptr + 1))
		return (NULL);
	output = ft_substr(buffer, (ptr - buffer) + 1, ft_strlen(ptr + 1));
	return (output);
}

/**
 * @brief Returns the remainder of the string if present and sets new remainder
 *
 * This function reads data from the remainder and finds the occurence of a
 * newline if found the string is returned and assigned to output the
 * remaining is duplicated and assigned to remainder
 *
 * @return A pointer to a dynamically allocated string containing the string
 *         following the newline character
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned line.
 * !STILL HAS MEM LEAKS, DOESN'T RETURN NULL IF REMAINDER IS EMPTY
 */
static char	*handle_remainder(char **remainder)
{
	char	*newline_ptr;
	char	*temp;
	char	*output;

	if (!*remainder)
		return (NULL);
	newline_ptr = ft_strchr(*remainder, NEWLINE);
	if (!newline_ptr)
	{
		output = ft_substr(*remainder, 0, ft_strlen(*remainder));
		free(*remainder);
		*remainder = NULL;
		return (output);
	}
	output = ft_substr(*remainder, 0, newline_ptr - *remainder + 1);
	temp = ft_substr(*remainder, newline_ptr - *remainder + 1,
			ft_strlen(newline_ptr));
	free(*remainder);
	if (ft_strlen(temp) == 0)
	{
		*remainder = NULL;
		free(temp);
	}
	else
		*remainder = temp;
	return (output);
}
