/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	write_in_file(t_app *app, char *filename, char *content, int append)
{
	int	fd;

	if (append)
		fd = open(filename,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	else
		fd = open(filename,
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd < 0)
	{
		str_error(app, filename);
		return ;
	}
	ft_putstr_fd(content, fd);
	close(fd);
}
