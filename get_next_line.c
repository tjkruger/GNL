/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
/*   Updated: 2024/11/15 13:57:12 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_until_newline(int fd, char **buffer)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (!ft_strchr(*buffer, '\n') && (bytes_read) > 0)
	{
		buf[bytes_read] = '\0';
		tmp = *buffer;
		*buffer = ft_strjoin(tmp, buf);
		free(tmp);
		if (!*buffer)
			return (-1);
	}
	if (bytes_read < 0)
		return (-1);
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
	static char	*buffers[1024];
	char		*line;
	char		*tmp;
	char		*newline_pos;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_until_newline(fd, &buffers[fd]) == -1 || (!buffers[fd]
			|| *buffers[fd] == '\0'))
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	newline_pos = ft_strchr(buffers[fd], '\n');
	line = extract_line_and_update_buffer(&buffers[fd]);
	return (line);
}
