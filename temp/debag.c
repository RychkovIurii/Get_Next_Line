#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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
char	*ft_remove_line(char *stack, char *line)
{
	char	*temp;

	temp = stack;
	stack = ft_strdup(stack + ft_strlen(line));
	free(temp);
	return (stack);
}

char	*ft_extract_line(char *stack)
{
	size_t	i;
	char	*line;

	i = 0;
	while (stack[i] != '\n' && stack[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stack[i] != '\n' && stack[i] != '\0')
	{
		line[i] = stack[i];
		i++;
	}
	line[i] = stack[i];
	line[i + 1] = '\0';
	return (line);
}

char	*ft_update_stack(char	**stack)
{
	char	*line;

	line = ft_extract_line(*stack);
	*stack = ft_remove_line(*stack, line);
	return (line);
}

char	*free_stuff(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (*ptr);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE];
	static char		*stack;
	ssize_t			bytes_read;
	size_t			len_stack;
	size_t			steps;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (stack && *stack)
			return (ft_update_stack(&stack));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free_stuff(&stack));
		len_stack = ft_strlen(stack);
		stack = (char *)malloc(sizeof(char) * (len_stack + bytes_read + 1));
		if (!stack)
			return (NULL);
		ft_strlcat_buf(stack, buffer, len_stack + bytes_read, bytes_read);
		steps = ft_newline_counter(stack);
		if (steps)
			return (ft_update_stack(&stack));
	}
	return (stack);
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
		printf("tulostaa rivin\n");
		printf("%s\n", line);
		free(line);
	}
	// Close the file
	close(fd);
	return (0);
}