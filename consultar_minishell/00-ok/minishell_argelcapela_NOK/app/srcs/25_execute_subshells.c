/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_execute_subshells.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 18:48:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	sub(t_ms *m, t_ms *ms, t_cmd **curr_cmd)
{
	m = &((*curr_cmd)->my_prompt->subs[
			(*curr_cmd)->my_prompt->i_subs]);
	if ((*curr_cmd)->input_fd > 0)
		dup2((*curr_cmd)->input_fd, 0);
	dup2((*curr_cmd)->pipe[1], 1);
	ms_subshell(m);
	ms_reinit(ms);
	exit(0);
}

int	execv_in_sub_shell(t_cmd **curr_cmd, t_ms *ms)
{
	t_ms	*m;
	int		subshell;

	m = NULL;
	pipe((*curr_cmd)->pipe);
	subshell = fork();
	if (subshell == 0)
		sub(m, ms, curr_cmd);
	waitpid(subshell, NULL, 0);
	(*curr_cmd)->input_fd = (*curr_cmd)->pipe[0];
	close((*curr_cmd)->pipe[1]);
	(*curr_cmd)->my_prompt->i_subs++;
	*curr_cmd = (*curr_cmd)->next;
	return (0);
}

int	ms_execute_prompt_in_subshell(t_ms *ms,
		t_p *curr_p, int *exit_code)
{
	int		child;
	t_ms	*current_sub;

	current_sub = &(curr_p->subs[curr_p->i_subs]);
	child = fork();
	if (child == 0)
	{
		ms_subshell(current_sub);
		ms_reinit(ms);
		exit(0);
	}
	ms_close_fds(curr_p);
	waitpid(child, exit_code, 0);
	return (1);
}
