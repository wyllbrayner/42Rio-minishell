/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/07 21:28:39 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_unset(t_ms *ms,
t_cmd *curr_cmd, t_p *curr_p)
{
	char	*key;

	key = curr_cmd->cmd_splited_by_space[1];
	if (ft_mtx_size((void **) curr_cmd->cmd_splited_by_space) <= 1)
		return ;
	if (key)
	{
		ms_delete_env(&ms->envs, key);
		ms_delete_env(&ms->aux_envs, key);
		set_exit_code(curr_cmd->my_prompt->ms, curr_p->cmds, 0);
	}
}
