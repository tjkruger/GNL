/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
/*   Updated: 2024/11/28 21:46:27 by tjkruger         ###   ########.fr       */
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

static int	read_until_newline(int fd, char *buffer)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*tmp;
	char	*joined;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		tmp = ft_strdup(buffer);
		if (tmp == NULL)
			return (-1);
		joined = ft_strjoin(tmp, buf);
		free(tmp);
		if (joined == NULL)
			return (-1);
		ft_substr(joined, 0, ft_strlen(joined), buffer);
		free(joined);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	if (bytes_read < 0)
		return (-1);
	return (1);
}

static char	*extract_line_and_update_buffer(char *buffer)
{
	char	*line;
	char	*newline_pos;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos != NULL)
	{
		line = ft_substr(buffer, 0, newline_pos - buffer + 1, buffer);
		buffer = ft_substr(buffer, newline_pos - buffer + 1, ft_strlen(buffer),
				buffer);
	}
	else
	{
		line = ft_strdup(buffer);
		buffer[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffers[1024][BUFFER_SIZE + 1];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_until_newline(fd, buffers[fd]) == -1 || buffers[fd][0] == '\0')
		return (NULL);
	return (extract_line_and_update_buffer(buffers[fd]));
}

#include "stdio.h"
#include <fcntl.h> // For open
#include <stdio.h> // For printf
#include <unistd.h> // For read and close

int	main(void)
{
	char	*tmp;

	int fd = open("test.txt", O_RDONLY); // Open the file for reading
	while ((tmp = get_next_line(fd)) != NULL)
	{
		printf("%s", tmp); // Print the line
	}
	close(fd);
	return (0);
}
