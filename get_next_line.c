/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:11 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/16 12:34:46 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;

	ptr_s = (char *)s;
	while (*ptr_s != (char)c)
	{
		if (*ptr_s == '\0')
		{
			return (NULL);
		}
		ptr_s++;
	}
	return (ptr_s);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*one_line;
	ssize_t	check_read;
	ssize_t	i;

	i = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	check_read = 1;
	one_line = NULL;
	while (check_read > 0)
	{
		one_line = ft_strjoin_buf(one_line, buffer, i);
		if (one_line[ft_strlen(one_line) - 1] == '\n')
			return (one_line);
		check_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (one_line);
}
