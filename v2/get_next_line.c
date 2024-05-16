/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:11 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/16 17:45:01 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	while (bytes_read >= 0)
	{
		if (stack && *stack)
			return (ft_update_stack(&stack));
		len_stack = ft_strlen(stack);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_stuff(&stack));
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
