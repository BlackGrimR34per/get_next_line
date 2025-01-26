/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:09:15 by ysheraun          #+#    #+#             */
/*   Updated: 2025/01/26 16:24:22 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	read_into_buffer(int fd, char **buffer, char *read_buffer);
static char	*extract_line(char *buffer);
static char	*update_buffer(char *buffer);

/**
 * @brief 	This function reads the next line from the specified 
 *			file descriptor and returns it. The line is delimited 
 			by the newline character, and each call to this function
			will return the next line in the file.
 * @param 	fd The file descriptor from which to read.
 * @return 	A string containing the next line from the file, including
 * 			 newline character.
 *         Returns NULL if the end of the file is reached or an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	char		*read_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	read_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	read_into_buffer(fd, &buffer[fd], read_buffer);
	free(read_buffer);
	if (!buffer[fd] || buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}

/*
 *	@brief 	Reads from the file descriptor into a static 
			buffer until a newline or the end of file is 
			encountered. If no data has been read yet,
			it initializes the buffer.
 * @param	fd	The file descriptor to read from.
 * @param	buffer	The static buffer that stores the read
 * 			data for the file.
 * @param	read_buffer	A temporary buffer used to store the
 *			raw data from the read operation.
 */
static void	read_into_buffer(int fd, char **buffer, char *read_buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return ;
		read_buffer[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, read_buffer);
		if (!*buffer || ft_strchr(*buffer, NEWLINE))
			return ;
	}
}

/**
 * @brief	Extracts a single line from the static buffer 
 *			up to the newline character (if present), or 
 			returns the entire buffer if no newline is found.
 * @param 	buffer The static buffer containing the data.
 * @return	A string containing the line extracted from the
 * 			buffer, up to the newline The string includes 
 * 			the newline character if present.
 */
static char	*extract_line(char *buffer)
{
	char	*line;
	char	*newline_pointer;
	size_t	len;

	if (!buffer)
		return (NULL);
	newline_pointer = ft_strchr(buffer, NEWLINE);
	if (!newline_pointer)
		len = ft_strlen(buffer);
	else
		len = (newline_pointer - buffer) + 1;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, len);
	line[len] = '\0';
	return (line);
}

/**
 * @brief 	Updates the static buffer by removing the 
 *			portion of the buffer that has been consumed 
 			(i.e., up to and including the first newline character).
 *        If no newline is found, it returns NULL as the buffer is empty.
 * @param buffer The static buffer that contains the remaining data.
 * @return	A new buffer containing the remaining data after the newline, 
 * 			or NULL if
 *         there is no remaining data.
 */
static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*newline_pointer;
	size_t	length;

	if (!buffer)
		return (NULL);
	newline_pointer = ft_strchr(buffer, NEWLINE);
	if (!newline_pointer || !*(newline_pointer + 1))
	{
		free(buffer);
		return (NULL);
	}
	length = ft_strlen(newline_pointer + 1);
	new_buffer = (char *)malloc(sizeof(char)
			* (length + 1));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, newline_pointer + 1, length);
	new_buffer[length] = '\0';
	free(buffer);
	return (new_buffer);
}
