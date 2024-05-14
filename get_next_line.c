/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:11 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/14 18:25:13 by irychkov         ###   ########.fr       */
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
	check_read = read(fd, buffer, BUFFER_SIZE);
	if (check_read <= 0 || buffer <= 0)
		return (NULL);
	one_line = ft_strjoin_buf("", buffer, check_read);
	while (check_read > 0)
	{
		while (i < check_read)
		{
			if (buffer[i] == '\n')
			{
				one_line = ft_strjoin_buf(one_line, buffer, i);
				return (one_line);
			}
			i++;
		}
		if (check_read > 0)
			one_line = ft_strjoin_buf(one_line, buffer, check_read);
	}
	return (one_line);
}
