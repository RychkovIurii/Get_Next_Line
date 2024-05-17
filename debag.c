/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debag.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:54:38 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/17 15:54:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t	ft_strlen_buf(const char	*str)
{
	ssize_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*free_stuff(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*ft_extract_line(char *stack)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	if (!(stack))
		return (NULL);
	while (stack[i] != '\n' && stack[i] != '\0')
		i++;
	if (stack[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stack[j];
		j++;
	}
	if (stack[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*ft_strlcat_buf(char *stack, char *buffer, ssize_t bytes_read)
{
	ssize_t		i;
	ssize_t		j;
	char		*new_stack;

	i = 0;
	j = 0;
	new_stack = NULL;
	if (bytes_read <= 0)
		return (stack);
	i = ft_strlen_buf(stack);
	new_stack = (char *)malloc((i + bytes_read + 1) * sizeof(char));
	if (!new_stack)
		return (free_stuff(&stack));
	while (stack != NULL && stack[j])
	{
		new_stack[j] = stack[j];
		j++;
	}
	j = 0;
	stack = free_stuff(&stack);
	while (j < bytes_read)
		new_stack[i++] = buffer[j++];
	new_stack[i] = 0;
	return (new_stack);
}

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
	static char		*stack;
	ssize_t			bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
				stack = free_stuff(&stack);
			if (stack && *stack)
				return (ft_update_stack(&stack));
			return (free_stuff(&stack));
		}
		stack = ft_strlcat_buf(stack, buffer, bytes_read);
		if (stack && ft_newline_counter(stack))
			return (ft_update_stack(&stack));
	}
	return (free_stuff(&stack));
}

int	main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	// Read lines from the file until end of file
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("result:\n");
		printf("%s", line);
		free(line);
	}
	// Close the file
	close(fd);
	return (0);
}