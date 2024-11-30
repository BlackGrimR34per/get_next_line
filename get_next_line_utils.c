/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:00:56 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/28 00:46:43 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strappend(char *dest, char *src)
{
	size_t	index;
	char	*string;
	char	*end;

	index = 0;
	end = ft_strchr(src, '\n');
	if (!end)
		end = src + ft_strlen(src);
	else
		end++;
	if (!dest)
		return (ft_substr(src, 0, end - src));
	string = (char *)malloc(ft_strlen(dest) + (end - src) + 1);
	if (!string)
		return (NULL);
	while (*dest)
		string[index++] = *dest++;
	while (src < end)
		string[index++] = *src++;
	string[index] = '\0';
	return (string);
}

char	*ft_strchr(const char *s, int c)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	int				index;
	unsigned int	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start >= length)
		len = 0;
	else if (start + len > length)
		len = length - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	index = 0;
	while (len--)
		ret[index++] = *(s + start++);
	ret[index] = '\0';
	return (ret);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}
