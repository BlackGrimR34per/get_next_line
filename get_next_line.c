/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:32:45 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/21 11:52:10 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*output;
	char	*temp;
	size_t	bytes_read;

	if (BUFFER_SIZE <= 0 || fd <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	output = malloc(sizeof(char));
	if (!output)
		return (NULL);
	bytes_read = read(fd, buffer, sizeof(buffer));
	*output = '\0';
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = output;
		output = ft_strappend(output, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (output);
}
