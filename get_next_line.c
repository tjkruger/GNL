/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
/*   Updated: 2024/12/01 18:19:39 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>  // For open
#include <stdio.h>  // For printf
#include <unistd.h> // For read and close

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	read_until_newline(int fd, char *buffer)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		ft_strcpy(buffer + ft_strlen(buffer), buf);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	return (bytes_read);
}

static char	*extract_line_and_update_buffer(char *buffer)
{
	char	*line;
	char	*newline_pos;
	size_t	len;

	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos)
		newline_pos = buffer + ft_strlen(buffer);
	len = newline_pos - buffer + 1;
	line = ft_substr(buffer, 0, len);
	if (*newline_pos == '\n')
		ft_strcpy(buffer, newline_pos + 1);
	else
		buffer[0] = '\0';
	buffer[ft_strlen(buffer)] = '\0';
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
