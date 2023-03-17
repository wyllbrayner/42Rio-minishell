/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:07:29 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/20 23:28:33 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line.h"

char	*read_file(int fd, char *backup);
char	*get_line(char *backup);
char	*save_line(char *backup);

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_file(fd, backup);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = save_line(backup);
	return (line);
}

char	*read_file(int fd, char *backup)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_gnl(backup, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		backup = ft_strjoin_gnl(backup, buff);
	}
	free(buff);
	return (backup);
}

char	*get_line(char *backup)
{
	int		i;
	char	*line;

	if (!backup[0])
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*save_line(char *backup)
{
	int		i;
	char	*save_line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	save_line = (char *)malloc(sizeof(char) * (ft_strlen_gnl(backup) - i + 1));
	if (!save_line)
		return (NULL);
	i++;
	ft_strlcpy_gnl(save_line, &backup[i], (ft_strlen_gnl(&backup[i]) + 1));
	free(backup);
	return (save_line);
}
