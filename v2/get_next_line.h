/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:42 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/16 17:44:59 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
ssize_t	ft_strlen(const char	*str);
char	*ft_strdup(const char *s1);
size_t	ft_newline_counter(char *stack);
size_t	ft_strlcat_buf(char *d, char *s, size_t size, size_t bytes_read);

#endif