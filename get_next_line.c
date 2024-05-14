/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:11 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/14 17:13:27 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#define BUFFER_SIZE 42

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*one_line;
	ssize_t	check_read;
	size_t	i;

	i = 0;
	check_write = read(fd, buffer, BUFFER_SIZE);

	if (check_write <= 0 || buffer <= 0)
		return (NULL);
	while (check_write > 0)
	{
		ft_strjoin_buf(one_line, char buffer[BUFFER_SIZE], size_t);
		return (one_line);
	}

}