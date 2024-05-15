/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:26 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/15 19:49:56 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	ft_strlcpy_buf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return ;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return ;
}

static void	ft_strlcat_buf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	size_remain;
	size_t	size_total;

	i = 0;
	dst_len = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= dst_len)
		return ;
	else
		size_remain = dstsize - dst_len - 1;
	while (src[i] && size_remain > i)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return ;
}

char	*ft_strjoin_buf(char const *stack, char *buffer, size_t i)
{
	char		*result;
	size_t		total_len;
	static char	*temp_line;

	while ((buffer[i] != '\0' && buffer[i] != '\n') && i < BUFFER_SIZE)
		i++;
	total_len = ft_strlen(stack) + i + 2 + ft_strlen(temp_line);
	result = (char *)malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	result[0] = '\0';
	if (temp_line)
	{
		ft_strlcpy_buf(result, temp_line, ft_strlen(temp_line) + 1);
		free(temp_line);
	}
	ft_strlcpy_buf(result, stack, ft_strlen(stack) + 1);
	ft_strlcat_buf(result, buffer, total_len);
	if (i < BUFFER_SIZE && buffer[i] == '\n')
	{
		temp_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE - i));
		if (!temp_line)
		{
			free(result);
			return (NULL);
		}
		ft_strlcpy_buf(temp_line, buffer + i + 1, (BUFFER_SIZE - i));
	}
	return (result);
}
