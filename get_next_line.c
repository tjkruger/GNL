/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
/*   Updated: 2024/12/03 14:46:22 by tjkruger         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	else
		return (NULL);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	index;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	index = 0;
	ft_strcpy(str, s1);
	ft_strcpy(str + len1, s2);
	str[len1 + len2] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffers[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	if (fd < 0 || read(fd, buffers, 0) < 0)
		return (NULL);
	line = ft_strjoin(line, buffers);
	bytes_read = 42;
	while (!ft_strchr(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffers, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (ft_strlen(line))
				return (line);
			return (NULL);
		}
		line = ft_strjoin(line, buffers);
		if (!line)
			return (NULL);
	}
	ft_strcpy(buffers, ft_strchr(line, '\n') + 1);
	*(ft_strchr(line, '\n') + 1) = 0;
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*tmp;

// 	int fd = open("/Users/tjkruger/Documents/getnextline/get_next_line.c",
// 					O_RDONLY); // Open the file for reading
// 	while ((tmp = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", tmp); // Print the line
// 		free(tmp);
// 	}
// 	close(fd);
// 	return (0);
// }
