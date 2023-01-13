/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_dup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:32:52 by argel             #+#    #+#             */
/*   Updated: 2022/12/14 07:38:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_fd_dup2(int read_from, int write_in)
{
	char	*line;

	line = get_next_line(read_from);
	while (line)
	{
		ft_putstr_fd(line, write_in);
		ft_free_ptr((void *) &line);
		line = get_next_line(read_from);
	}
	ft_free_ptr((void *) &line);
	close(read_from);
	close(write_in);
}
