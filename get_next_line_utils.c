/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:33:17 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/26 19:49:31 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strappend(char *dest, char *src)
{
	size_t	index;
	char	*string;
	char	*end;

	if (!src)
		return (dest);
	index = 0;
	end = ft_strchr(src, '\n');
	if (!end)
		end = src + ft_strlen(src);
	else
		end++;
	string = (char *)malloc(ft_strlen(dest) + (end - src) + 1);
	while (*dest)
		string[index++] = *dest++;
	while (src < end)
		string[index++] = *src++;
	string[index] = '\0';
	return (string);
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

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dest;
	size_t	length;

	if (s1 == NULL)
		return (NULL);
	i = -1;
	length = ft_strlen(s1);
	dest = (char *)malloc((sizeof(char) * length) + 1);
	if (!dest)
		return (0);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
