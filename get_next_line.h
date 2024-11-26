/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:06:23 by yosherau          #+#    #+#             */
/*   Updated: 2024/11/26 15:42:08 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 56
# endif

# define NEWLINE '\n'

char	*get_next_line(int fd);
char	*ft_strappend(char *dest, char *src);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);

#endif