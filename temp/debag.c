#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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
			return one_line;
		check_read = read(fd, buffer, BUFFER_SIZE);
	}
	return one_line;
}

/* void free_stuff(**ptr)
{
	free(*ptr);
	*ptr = NULL;
} */

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