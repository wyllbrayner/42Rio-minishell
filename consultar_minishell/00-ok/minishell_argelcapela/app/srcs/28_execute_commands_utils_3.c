/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_execute_commands_utils_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/17 16:01:53 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_which_command_type(t_p *curr_p, \
t_cmd *curr_cmd, t_ms *ms)
{
	is_input_command(curr_cmd->cmd_line);
	if (ft_strncmp(curr_cmd->just_name, "history", 7) == 0)
	{
		ms_print_history(ms, curr_cmd, curr_p);
		if (curr_cmd->index == (curr_p->args_amount - 1))
			return (1);
	}
	else if (is_builtin(curr_cmd->just_name))
		execute_builtin(ms, curr_cmd, curr_p);
	else if (curr_cmd->can_execute == 1)
	{
		if (curr_cmd->index > 0 && curr_cmd->prev->input_fd > 2
			&& curr_cmd->input_fd == 0)
			curr_cmd->input_fd = curr_cmd->prev->input_fd;
		ms_execute_command(curr_p, curr_cmd, \
			ms->envp, &curr_cmd->input_fd);
	}
	return (0);
}

void	ms_execute_command(t_p *prompt, \
t_cmd *curr_cmd, char **envp, int *aux_fd)
{
	int	child_process_id;

	pipe(curr_cmd->pipe);
	child_process_id = get_child_process_id(prompt, curr_cmd, envp, aux_fd);
	if ((prompt->n_cmds - 1) == curr_cmd->index)
	{
		waitpid(child_process_id, &curr_cmd->exit_code, 0);
		if (curr_cmd->exit_code && curr_cmd->exit_code != 127)
			curr_cmd->exit_code = WEXITSTATUS(curr_cmd->exit_code);
	}
	if (*aux_fd > 2)
		close (*aux_fd);
	*aux_fd = curr_cmd->pipe[0];
	close(curr_cmd->pipe[1]);
}

int	get_child_process_id(const t_p *prompt, \
	t_cmd *curr_cmd, char **envp, const int *aux_fd)
{
	int	child_process_id;

	child_process_id = fork();
	if ((prompt->n_cmds > 1)
		&& ((prompt->n_cmds - 1) == curr_cmd->index))
		signal(SIGINT, SIG_IGN);
	if (child_process_id == 0)
	{
		dup2(*aux_fd, 0);
		if ((prompt->n_cmds - 1) == curr_cmd->index)
		{
			if (prompt->n_cmds > 1)
				signal(SIGINT, SIG_IGN);
			dup2(curr_cmd->output_fd, 1);
		}
		else
			dup2(curr_cmd->pipe[1], 1);
		if (execve(curr_cmd->path_and_name, ft_mtx_replace_all_special(
					curr_cmd->cmd_splited_by_space, curr_cmd), envp) == -1)
			exit(127);
	}
	return (child_process_id);
}
