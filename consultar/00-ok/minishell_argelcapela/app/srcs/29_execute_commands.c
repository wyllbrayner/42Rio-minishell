/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:11 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_execv(t_ms *ms, t_p *curr_p, t_cmd **curr_cmd)
{
	if (ft_strncmp((*curr_cmd)->just_name, "cat",
			ft_strlen((*curr_cmd)->just_name)) == 0)
	{
		if (ms->fake_cat_input > 0)
		{
			(*curr_cmd) = (*curr_cmd)->next;
			return (1);
		}
	}
	if (ms_which_command_type(curr_p,
			(*curr_cmd), ms))
		return (1);
	return (-1);
}

int	ms_execute_commands_loop(t_ms *ms, t_cmd *curr_cmd, t_p *curr_p)
{
	int	res;

	res = 0;
	if (curr_cmd->can_execute == -1)
	{
		curr_cmd = curr_cmd->next;
		return (3);
	}
	if (curr_cmd->subshell)
	{
		if (execv_in_sub_shell(&curr_cmd, ms) == 2)
			return (2);
	}
	else
		res = ms_execv(ms, curr_p, &curr_cmd);
	if (res == 1)
		return (2);
	return (-1);
}

int	ms_execute_commands(t_ms *ms, t_p *curr_p)
{
	t_cmd	*curr_cmd;
	int		res;

	curr_cmd = curr_p->cmds;
	res = -1;
	pre_cat_ls_sc(ms, &curr_cmd);
	while (curr_cmd)
	{
		if (!curr_cmd->can_execute)
		{
			curr_cmd = curr_cmd->next;
			continue ;
		}
		res = ms_execute_commands_loop(ms, curr_cmd, curr_p);
		if (res != -1)
			return (res);
		set_exit_code(curr_p->ms, curr_cmd, -1);
		curr_cmd = curr_cmd->next;
	}
	exec_cat_ls_sc(ms);
	ms_close_fds(curr_p);
	curr_cmd = ms_dll_cmd_last(curr_p->cmds);
	return (curr_cmd->exit_code);
}

static void	print_fd_or_execute_cmd_loop(t_ms *ms, t_p *curr_p)
{
	int		exit_code;
	char	*tmp;
	int		i;

	i = 0;
	while (curr_p)
	{
		tmp = ft_strtrim(curr_p->this_p_line, " ");
		if (ft_strncmp(tmp, T_SUBSHELL, \
ft_strlen(curr_p->this_p_line)) == 0)
			ms_execute_prompt_in_subshell(ms, curr_p, &exit_code);
		else
		{
			ft_free_ptr((void *) &tmp);
			exit_code = ms_execute_commands(ms, curr_p);
		}
		ft_free_ptr((void *) &tmp);
		if (ms->connectors_order != NULL)
			if ((ms->connectors_order[i] == 1 && exit_code != 0)
				|| (ms->connectors_order[i] == 2 && exit_code == 0))
				break ;
		ft_free_ptr((void *) &tmp);
		i++;
		curr_p = curr_p->next;
	}
}

void	ms_execute(t_ms *ms)
{
	t_p	*curr_p;

	curr_p = ms->p;
	print_fd_or_execute_cmd_loop(ms, curr_p);
}
