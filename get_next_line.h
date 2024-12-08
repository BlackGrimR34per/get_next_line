/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:05:47 by ysheraun          #+#    #+#             */
/*   Updated: 2024/12/08 17:44:22 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define NEWLINE '\n'

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

void	*ft_memcpy(void *dst, void *src, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*get_next_line(int fd);

#endif