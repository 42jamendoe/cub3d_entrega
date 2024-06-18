/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:50 by jamendoe          #+#    #+#             */
/*   Updated: 2022/12/09 18:39:42 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

char	*ft_new_buffer(char *buffer, char *nextbuffer, int i, int buffer_len)
{
	int	j;

	j = 0;
	while (i + j <= buffer_len)
	{
		buffer[j] = nextbuffer[i + j];
		j++;
	}
	free(nextbuffer);
	return (buffer);
}

char	*ft_next_buffer(char *buffer)
{
	char	*nextbuffer;
	int		i;
	int		buffer_len;

	i = 0;
	if (!buffer)
		return (NULL);
	buffer_len = ft_strlen(buffer);
	if (!ft_strchr(buffer, '\n'))
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (NULL);
	nextbuffer = buffer;
	buffer = (char *)malloc(sizeof(char) * (buffer_len - i));
	if (!buffer)
		return (NULL);
	i++;
	buffer = ft_new_buffer(buffer, nextbuffer, i, buffer_len);
	return (buffer);
}

char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{	
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_buffer(int fd, char *buffer)
{
	char	*tmp;
	char	*totalbuffer;
	int		bytes_read;

	tmp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		totalbuffer = buffer;
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin(totalbuffer, tmp);
		free(totalbuffer);
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4096)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = (char *)malloc(sizeof(char) * 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = ft_buffer(fd, buffer[fd]);
	line = ft_next_line(buffer[fd]);
	buffer[fd] = ft_next_buffer(buffer[fd]);
	return (line);
}
/* 
int	main(void)
{
	int	fd[4096];

	//fd[0] = open("test", O_RDWR);
	fd[0] = open("41_with_nl", O_RDWR);
	fd[1] = open("42_with_nl", O_RDWR);
	fd[2] = open("43_with_nl", O_RDWR);
	printf("%s", get_next_line(1000));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(1001));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(1002));
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(1003));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(1004));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(1005));
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(fd[2]));
	return (0);
}
 */