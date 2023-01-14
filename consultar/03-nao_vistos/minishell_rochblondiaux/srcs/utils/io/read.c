/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_read(t_app *app, int fd)
{
	char	*buffer;
	int		red;

	buffer = malloc(READ_BUFFER_SIZE + 1);
	if (!buffer)
	{
		str_error(app, MALLOC_ERROR);
		return (NULL);
	}
	red = read(fd, buffer, READ_BUFFER_SIZE);
	if (red <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[red] = '\0';
	return (buffer);
}

char	*read_file(t_app *app, char *path)
{
	int		fd;
	char	*content;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		str_error(app, path);
		return (NULL);
	}
	tmp = ft_read(app, fd);
	content = NULL;
	while (tmp)
	{
		if (!content)
			content = tmp;
		else
			content = ft_strjoin_properly(content, tmp);
		tmp = ft_read(app, fd);
	}
	return (content);
}
