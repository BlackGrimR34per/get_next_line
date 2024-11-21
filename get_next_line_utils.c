/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:33:17 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/21 11:39:55 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strappend(char *dest, char *src)
{
	size_t	index;
	char	*string;
	char	*end;

	if (!src)
		return (NULL);
	else
	{
		index = 0;
		end = ft_strchr(src, '\n');
		string = (char *)malloc(ft_strlen(dest) + (end - src) + 1);
		while (*dest || (*src && src != end))
		{
			if (*dest)
				string[index++] = *dest++;
			else
				string[index++] = *src++;
		}
		string[index] = '\0';
		return (string);
	}
}

size_t	ft_strlen(char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*ft_strchr(char *s, int c)
{
	c = (unsigned char)c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
