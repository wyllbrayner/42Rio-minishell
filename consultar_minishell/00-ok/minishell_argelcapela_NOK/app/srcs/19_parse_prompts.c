/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19_parse_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:39:53 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/15 18:45:22 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	reset_prompt(t_p **curr_p)
{
	(*curr_p) = (*curr_p)->next;
	(*curr_p)->next = NULL;
	(*curr_p)->has_here_doc = 0;
	(*curr_p)->hd_limiter = NULL;
	(*curr_p)->input_fd = -1;
	(*curr_p)->input_path = NULL;
	(*curr_p)->input_redirected_to_file = 0;
	(*curr_p)->no_cmd_just_redirect = 0;
	(*curr_p)->output_fd = 1;
	(*curr_p)->output_path = NULL;
	(*curr_p)->redirect = 0;
	(*curr_p)->n_cmds = 0;
	(*curr_p)->cmds = NULL;
	(*curr_p)->aux_fd = 0;
	(*curr_p)->this_p_line = NULL;
	(*curr_p)->this_p_line_splited_by_pipe = NULL;
	(*curr_p)->args_amount = 0;
	(*curr_p)->has_here_doc = 0;
	(*curr_p)->no_cmd_just_redirect = 0;
	(*curr_p)->input_redirected_to_file = 0;
	(*curr_p)->i_subs = 0;
	(*curr_p)->n_subs = 0;
}

static void	ms_get_prompt_2(t_p *curr_p)
{
	ft_mtx_free((void **) curr_p->this_p_line_splited_by_pipe);
	curr_p->this_p_line_splited_by_pipe = \
	ft_split_by_str(curr_p->this_p_line, T_PIPE);
	curr_p->args_amount = ft_mtx_size((void **) \
	curr_p->this_p_line_splited_by_pipe);
}

t_p	*ms_get_prompt(t_ms *ms, t_p *curr_p, int i)
{
	if (i >= 1)
	{
		curr_p->next = (t_p *) ft_calloc (1, sizeof(t_p));
		curr_p->next->prev = curr_p;
		reset_prompt(&curr_p);
	}
	if (ms->slt_splited_by_connectors)
		curr_p->this_p_line = ft_strdup(ms->slt_splited_by_connectors[i]);
	else
		curr_p->this_p_line = ft_strdup(ms->shell_line_tokenized);
	curr_p->ms = ms;
	ms_parse_subshells(&curr_p);
	ms_get_prompt_2(curr_p);
	return (curr_p);
}

static void	ms_connectors_order(t_ms *ms, t_psub *psub)
{
	int	i;
	int	z;

	if (psub != NULL)
	{
		free_ssub(psub->ssub);
		ft_free_ptr((void *) &psub);
	}
	i = 0;
	z = 0;
	ms->connectors_order = ft_calloc ((ms->p_amount) + 1, sizeof(int));
	while (ms->shell_line[i])
	{
		if (ms->shell_line[i]
			&& (ft_strncmp(&ms->shell_line[i], "&&", 2) == 0))
				ms->connectors_order[z++] = 1;
		else if (ms->shell_line[i]
			&& (ft_strncmp(&ms->shell_line[i], "||", 2) == 0))
				ms->connectors_order[z++] = 2;
		i++;
	}
}

t_p	*parse_prompts(t_ms *ms)
{
	t_psub	*psub;

	psub = NULL;
	if (ft_strnstr(ms->shell_line_tokenized, \
		T_CONNECTOR, ft_strlen(ms->shell_line_tokenized)))
	{
		psub = token_subshells_pre_split_connectors(ms);
		ms->slt_splited_by_connectors = \
			ft_split_by_str(ms->shell_line_tokenized, T_CONNECTOR);
		ms->p_amount = ft_mtx_size((void **) ms->slt_splited_by_connectors);
		if (psub)
			psub->head = psub->ssub;
		untoken_subshells_pos_split_connectors(ms, psub);
		ms_connectors_order(ms, psub);
	}
	else
	{
		ms->slt_splited_by_connectors = NULL;
		ms->connectors_order = NULL;
	}
	ms->p = (t_p *) ft_calloc(1, sizeof(t_p));
	ms->p->next = NULL;
	ms->p->prev = NULL;
	return (ms->p);
}
