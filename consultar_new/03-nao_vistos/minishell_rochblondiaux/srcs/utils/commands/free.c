/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:32:24 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_command(t_command *cmd)
{
	free(cmd->name);
	free(cmd->executable);
	free_redirections(&cmd->redirections);
	free_array(cmd->args);
	free(cmd);
}

void	free_command_map(t_command **map)
{
	size_t	index;

	index = -1;
	while (map[++index])
		free_command(map[index]);
	free(map);
}
