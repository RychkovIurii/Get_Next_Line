/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:26 by irychkov          #+#    #+#             */
/*   Updated: 2024/05/17 15:42:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
