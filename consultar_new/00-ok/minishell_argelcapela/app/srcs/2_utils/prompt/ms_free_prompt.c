/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:54:01 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/07 16:54:08 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_free_subshells(t_p *curr_p)
{
	int	i;

	i = 0;
	while (i < curr_p->n_subs)
	{
		ms_finish((void *) &curr_p->subs[i]);
		i++;
	}
	curr_p->n_subs = 0;
	curr_p->i_subs = 0;
}

static void	free_curr_p(t_p *curr_p)
{
	if (!curr_p)
		return ;
	while (curr_p->next != NULL)
		curr_p = curr_p->next;
	while (curr_p->prev)
	{
		curr_p = curr_p->prev;
		ms_free_subshells(curr_p->next);
		if (curr_p->next->cmds != NULL)
			ms_dll_cmd_free(curr_p->next->cmds);
		if (curr_p->next->this_p_line != NULL)
			ft_free_ptr((void *) &curr_p->next->this_p_line);
		if (curr_p->next->this_p_line_splited_by_pipe != NULL)
			ft_mtx_free((void **) \
				curr_p->next->this_p_line_splited_by_pipe);
		if (curr_p->next->output_path != NULL)
			ft_free_ptr((void *) &curr_p->next->output_path);
		ft_free_ptr((void *) &curr_p->next->hd_limiter);
		if (curr_p->next != NULL)
			ft_free_ptr((void *) &curr_p->next);
	}
}

void	ms_free_prompt(t_ms *ms)
{
	free_curr_p(ms->p);
	if (ms->p == NULL)
		return ;
	ms_free_subshells(ms->p);
	if (ms->p->cmds != NULL)
		ms_dll_cmd_free(ms->p->cmds);
	if (ms->p->this_p_line != NULL)
		ft_free_ptr((void *) &ms->p->this_p_line);
	if (ms->p->this_p_line_splited_by_pipe != NULL)
		ft_mtx_free((void **) ms->p->this_p_line_splited_by_pipe);
	if (ms->p->output_path != NULL)
		ft_free_ptr((void *) &ms->p->output_path);
	ft_free_ptr((void *) &ms->p->hd_limiter);
	if (ms->p != NULL)
		ft_free_ptr((void *) &ms->p);
}
