/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:26 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/16 17:45:00 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strlen(const char	*str)
{
	ssize_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dst;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (src_len + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_newline_counter(char *stack)
{
	size_t	counter;
	size_t	i;

	i = 0;
	counter = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			counter++;
		i++;
	}
	return (counter);
}

size_t	ft_strlcat_buf(char *d, char *s, size_t size, size_t bytes_read)
{
	size_t	i;
	size_t	dst_len;
	size_t	size_remain;
	size_t	size_total;

	i = 0;
	dst_len = ft_strlen(d);
	size_total = dst_len + bytes_read;
	if (size == 0 || size <= dst_len)
		return (bytes_read + size);
	else
		size_remain = size - dst_len - 1;
	while (i < bytes_read && size_remain > i)
	{
		d[dst_len + i] = s[i];
		i++;
	}
	d[dst_len + i] = s[i];
	d[dst_len + i + 1] = '\0';
	return (size_total);
}
