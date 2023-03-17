/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dll_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/06 08:36:46 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	free_cmd_aux(t_cmd *cmds)
{
	if (cmds->input_fd > 2)
		close(cmds->input_fd);
	if (cmds->output_fd > 2)
		close(cmds->output_fd);
	if (cmds->pipe[0] > 2)
		close(cmds->pipe[0]);
	if (cmds->pipe[1] > 2)
		close(cmds->pipe[1]);
}

static void	free_all_cmd(t_cmd *cmds)
{
	while (cmds->next != NULL)
		cmds = cmds->next;
	while (cmds->prev != NULL)
	{
		cmds = cmds->prev;
		if (cmds->next->path_and_name)
			ft_free_ptr((void *) &cmds->next->path_and_name);
		if (cmds->next->just_name)
			ft_free_ptr((void *) &cmds->next->just_name);
		if (cmds->next->cmd_line)
			ft_free_ptr((void *) &cmds->next->cmd_line);
		if (cmds->symbol_path)
			ft_free_ptr((void *) &cmds->symbol_path);
		if (cmds->next->cmd_splited_by_space)
			ft_mtx_free((void **) cmds->next->cmd_splited_by_space);
		free_cmd_aux(cmds);
		if (cmds->next)
			ft_free_ptr((void *) &cmds->next);
	}
}

void	ms_dll_cmd_free(t_cmd *cmds)
{
	free_all_cmd(cmds);
	if (cmds->path_and_name != NULL)
		ft_free_ptr((void *) &cmds->path_and_name);
	if (cmds->just_name)
		ft_free_ptr((void *) &cmds->just_name);
	if (cmds->cmd_line)
		ft_free_ptr((void *) &cmds->cmd_line);
	if (cmds->symbol_path)
		ft_free_ptr((void *) &cmds->symbol_path);
	if (cmds->cmd_splited_by_space)
		ft_mtx_free((void **) cmds->cmd_splited_by_space);
	free_cmd_aux(cmds);
	if (cmds)
		ft_free_ptr((void *) &cmds);
}
