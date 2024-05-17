/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:25:07 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/17 16:51:47 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_newline_counter(char *stack)
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

static char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dst;
	size_t	src_len;

	i = 0;
	if (!s1)
		return (NULL);
	src_len = ft_strlen_buf(s1);
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

static char	*ft_remove_line(char *stack, char *line)
{
	char	*new_stack;
	size_t	line_len;
	size_t	stack_len;

	line_len = ft_strlen_buf(line);
	stack_len = ft_strlen_buf(stack);
	if (line_len >= stack_len)
		return (free_stuff(&stack));
	new_stack = ft_strdup(stack + line_len);
	free_stuff(&stack);
	return (new_stack);
}

static char	*ft_update_stack(char	**stack)
{
	char	*line;

	if (!(*stack))
		return (NULL);
	line = ft_extract_line(*stack);
	if (line)
		*stack = ft_remove_line(*stack, line);
	if (!line)
		free_stuff(&*stack);
	return (line);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE];
	static t_gnl	fd_array[MAX_FD];
	ssize_t			bytes_read;
	int				i;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes_read = 1;
	i = -1;
	while (++i < MAX_FD)
	{
		if (fd_array[i].fd == fd || fd_array[i].fd == 0)
		{
			fd_array[i].fd = fd;
			break ;
		}
	}
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
				fd_array[i].stack = free_stuff(&fd_array[i].stack);
			if (fd_array[i].stack && *fd_array[i].stack)
				return (ft_update_stack(&fd_array[i].stack));
			return (free_stuff(&fd_array[i].stack));
		}
		fd_array[i].stack = ft_strlcat_buf(fd_array[i].stack, buffer, bytes_read);
		if (fd_array[i].stack && ft_newline_counter(fd_array[i].stack))
			return (ft_update_stack(&fd_array[i].stack));
	}
	return (free_stuff(&fd_array[i].stack));
}
