/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssiddiqu <ssiddiqu@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:29:31 by ssiddiqu          #+#    #+#             */
/*   Updated: 2024/03/01 16:23:35 by ssiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE > INT_MAX || BUFFER_SIZE < 0)
		return (0);
	buffer = read_line(buffer, fd);
	if (!buffer)
		return (NULL);
	line = each_line(buffer);
	buffer = remaining_line(buffer);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	i = 0;
// 	while (line)
// 	{
// 		printf("[%d]: %s", i + 1, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close (fd);
// }

// int	main(void)
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	i = 0;
// 	while (line)
// 	{
// 		printf("[%d] : %s", i + 1, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }


int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		printf("[%d] : %s", i + 1, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

