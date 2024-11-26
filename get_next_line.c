/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
/*   Updated: 2024/11/26 19:27:10 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	read_until_newline(int fd, char **buffer)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		tmp = *buffer;
		*buffer = ft_strjoin(tmp, buf);
		free(tmp);
		if (!*buffer)
			return (-1);
		if (ft_strchr(*buffer, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	return (1);
}

static char	*extract_line_and_update_buffer(char **buffer)
{
	char	*line;
	char	*tmp;
	char	*newline_pos;

	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
		tmp = ft_strdup(newline_pos + 1);
		free(*buffer);
		*buffer = tmp;
		if (*buffer && **buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
		}
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffers[1024][BUFFER_SIZE + 1];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_until_newline(fd, &buffers[fd]) == -1 || (!buffers[fd]
			|| *buffers[fd] == '\0'))
	{
		buffers[fd][0] = '\0';
		return (NULL);
	}
	return (extract_line_and_update_buffer(&buffers[fd]));
}
