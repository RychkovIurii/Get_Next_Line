/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:26 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/14 19:54:49 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcpy_buf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = BUFFER_SIZE;
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static size_t	ft_strlcat_buf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	size_remain;
	size_t	size_total;

	i = 0;
	dst_len = ft_strlen(dst);
	size_total = dst_len + BUFFER_SIZE;
	if (dstsize == 0 || dstsize <= dst_len)
		return (BUFFER_SIZE + dstsize);
	else
		size_remain = dstsize - dst_len - 1;
	while (src[i] && size_remain > i)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (size_total);
}

char	*ft_strjoin_buf(char const *stack, char buffer[BUFFER_SIZE], size_t i)
{
	char		*result;
	size_t		total_len;
	static char	*temp_line;

	result = NULL;
	while ((buffer[i] != '\0' && buffer[i] != '\n') && i < BUFFER_SIZE)
		i++;
	if (i < BUFFER_SIZE && temp_line)
	{
		temp_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
		if (!temp_line)
		{
			free(result);
			return (NULL);
		}
		ft_strlcpy_buf(temp_line, buffer + i, (BUFFER_SIZE - i + 1));
	}
	total_len = ft_strlen(stack) + i + 1;
	result = (char *)malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	ft_strlcpy_buf(result, stack, ft_strlen(stack) + 1);
	ft_strlcat_buf(result, buffer, total_len);
	return (result);
}
