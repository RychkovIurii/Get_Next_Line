/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:11 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/14 19:54:32 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*one_line;
	ssize_t	check_read;
	ssize_t	i;

	i = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	check_read = read(fd, buffer, BUFFER_SIZE);
	if (check_read <= 0)
		return (NULL);
	one_line = ft_strjoin_buf("", buffer, i);
	while (check_read > 0)
	{
		check_read = read(fd, buffer, BUFFER_SIZE);
		if (check_read < 0)
		{
			free(one_line);
			return (NULL);
		}
		else if (check_read < 0)
			return (one_line);
		one_line = ft_strjoin_buf(one_line, buffer, i);
	}
	return (one_line);
}
