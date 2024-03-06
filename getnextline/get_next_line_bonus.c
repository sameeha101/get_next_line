/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:27:01 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/02/23 18:11:17 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(char *s, int fd)
{
	int		read_char;
	char	*buffer;

	read_char = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(s, '\n') && read_char != 0)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(s);
			free(buffer);
			return (NULL);
		}
		buffer[read_char] = '\0';
		s = ft_strjoin(s, buffer);
	}
	free(buffer);
	return (s);
}

char	*each_line(char *s1)
{
	int		i;
	char	*store;

	if (!*s1)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	store = malloc(sizeof(char) * (i + 2));
	if (!store)
		return (free(s1), NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		store[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		store[i] = s1[i];
		i++;
	}
	store[i] = '\0';
	return (store);
}

char	*remaining_line(char *s2)
{
	int		i;
	int		j;
	char	*store2;

	if (!s2 || s2[0] == '\0')
		return (free(s2), NULL);
	i = 0;
	while (s2[i] && s2[i] != '\n')
		i++;
	if (s2[i] == '\0')
	{
		return (free(s2), NULL);
	}
	j = 0;
	store2 = malloc(sizeof(char) * (ft_strlen(s2) - i + 1));
	if (!store2)
		return (free(s2), NULL);
	i++;
	while (s2[i])
	{
		store2[j++] = s2[i++];
	}
	store2[j] = '\0';
	return (free(s2), store2);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAXFD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE > INT_MAX || BUFFER_SIZE < 0 || fd > MAXFD)
		return (0);
	buffer[fd] = read_line(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = each_line(buffer[fd]);
	buffer[fd] = remaining_line(buffer[fd]);
	return (line);
}

int main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	// int i = 0;
	while (line)
	{
		line = get_next_line(fd1);
		printf("line 1: %s\n", line);
		free(line);
		line = get_next_line(fd2);
		printf("line 2: %s\n", line);
		free(line);
		line = get_next_line(fd3);
		printf("line 3: %s\n", line);
		free(line);
	
	}
	close(fd1);
	close(fd2);
	close(fd3);
}
