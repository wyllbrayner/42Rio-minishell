/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_parse_input_output_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:19 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 17:29:36 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

//2b!
int	output_fd(t_cmd **curr_cmd)
{
	int	fd;

	fd = 1;
	(*curr_cmd)->symbol_path = \
ft_super_replace_all((*curr_cmd)->symbol_path, 2, T_SPACE, " ");
	if ((*curr_cmd)->type == 2)
		fd = open((*curr_cmd)->symbol_path,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if ((*curr_cmd)->type == 0)
		fd = open((*curr_cmd)->symbol_path,
				O_CREAT | O_WRONLY | O_APPEND, 0777);
	return (fd);
}
