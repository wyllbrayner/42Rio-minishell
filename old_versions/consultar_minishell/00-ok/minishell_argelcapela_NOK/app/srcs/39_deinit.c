/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 16:27:32 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	free_ssub(t_ssub *ssub)
{
	t_ssub	*head;
	t_ssub	*del;

	head = ssub;
	while (head->next)
		head = head->next;
	while (head->prev)
	{
		del = head;
		if (head->prev)
			head = head->prev;
		ft_free_ptr((void *) &del->str);
		ft_free_ptr((void *) &del);
	}
	ft_free_ptr((void *) &head->str);
	ft_free_ptr((void *) &head);
}

static void	ms_finish_aux(t_ms *ms)
{
	if (ms->tmp != NULL)
		ft_free_ptr((void *) &ms->tmp);
	if (ms->tmp2 != NULL)
		ft_free_ptr((void *) &ms->tmp2);
	if (ms->aux != NULL)
		ft_free_ptr((void *) &ms->aux);
	if (ms->shell_line)
		ft_free_ptr((void *) &ms->shell_line);
	if (ms->p)
		ms_free_prompt(ms);
	if (ms->shell_line_tokenized)
		ft_free_ptr((void *) &ms->shell_line_tokenized);
	if (ms->readline_var)
		ft_free_ptr((void *) &ms->readline_var);
	ft_free_ptr((void *) &ms->connectors_order);
	if (ms->qs)
		ft_free_ptr((void *) &ms->qs);
	if (ms != NULL)
		ft_free_ptr((void *) &ms);
}

void	ms_finish(t_ms *ms)
{
	ft_free_ptr((void *) &ms->connectors_order);
	ms_free_history(ms);
	ms_free_env(ms->envs);
	ms_free_env(ms->aux_envs);
	ms_finish_aux(ms);
}

void	ms_reinit(t_ms *ms)
{
	ms->p_amount = 1;
	ms->input_command_open = 0;
	ms->no_path = 0;
	ms->force_stop = 0;
	ms_free_prompt(ms);
	ft_free_ptr((void *) &ms->tmp);
	ft_free_ptr((void *) &ms->tmp2);
	ft_free_ptr((void *) &ms->aux);
	ft_free_ptr((void *) &ms->sh_name);
	ft_free_ptr((void *) &ms->qs);
	ft_free_ptr((void *) &ms->connectors_order);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_mtx_free((void **) ms->slt_splited_by_connectors);
}
