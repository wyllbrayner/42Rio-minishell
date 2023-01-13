/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_cmd_add_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ft_dll_cmd_add_back(t_ms *ms, char **cmd_splited)
{
	t_cmd	*cmd;
	t_cmd	*last;

	last = NULL;
	cmd = ms->p.cmds;
	if (cmd == NULL)
	{
		cmd = (t_cmd *) malloc(sizeof(t_cmd));
		cmd->prev = NULL;
		cmd->next = NULL;
	}
	else
	{
		last = ft_dll_cmd_last(cmd);
		last->next = (t_cmd *) malloc(sizeof(t_cmd));
		cmd = last->next;
		cmd->prev = last;
		cmd->next = NULL;
	}
	cmd->cmd_splited = cmd_splited;
	cmd->name_and_path = NULL;
	cmd->index = 0;
	cmd->std_in = 0;
	cmd->subshell = 0;
}
