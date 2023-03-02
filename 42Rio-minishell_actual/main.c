/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/get_next_line.h"

#include <fcntl.h>  /* open   */
#include <unistd.h> /* close  */
#include <stdio.h>  /* printf */

int	main(void)
{
	int		fd;
	char	*retgnl;

	fd = open("teste0.txt", O_RDWR);
	if (fd < 0)
	{
		close(fd);
		return (-1);
	}
	while ((retgnl = get_next_line(fd)))
	{
		printf("%s", retgnl);
		free(retgnl);
	}
//	free(retgnl);
	close(fd);
	return (0);
}
