/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_execute_commands_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 16:45:46 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_close_fds(t_p *curr_p)
{
	t_cmd	*head;

	head = curr_p->cmds;
	while (head)
	{	
		if (head->input_fd > 2)
			close(head->input_fd);
		if (head->output_fd > 2)
			close(head->output_fd);
		head = head->next;
	}
}

static int	iterate_cmd_count_cat(t_ms *ms, t_cmd **tmp)
{
	char	*trim;

	trim = NULL;
	trim = ft_strtrim((*tmp)->cmd_line_pre_cat, " ");
	if (ft_strncmp(trim, "cat", ft_strlen(trim)) == 0
		&& (*tmp)->index == 0)
		ms->is_cat_sequence = 1;
	if (ms->is_cat_sequence)
	{
		while (tmp && ft_strncmp(trim, "cat", ft_strlen(trim)) == 0)
		{
			ms->fake_cat_input++;
			(*tmp) = (*tmp)->next;
			ft_free_ptr((void *) &trim);
			if ((*tmp) == NULL)
				break ;
			trim = ft_strtrim((*tmp)->cmd_line, " ");
		}
		ft_free_ptr((void *) &trim);
		return (1);
	}
	ft_free_ptr((void *) &trim);
	return (0);
}

int	pre_cat_ls_sc(t_ms *ms, t_cmd **curr_cmd)
{
	t_cmd	*tmp;
	t_p		*curr_p;

	curr_p = (*curr_cmd)->my_prompt;
	ms->fake_cat_input = 0;
	ms->is_cat_sequence = 0;
	if (curr_p->n_cmds <= 1
		|| (*curr_cmd)->can_execute == 0
		|| (*curr_cmd)->pre_cat)
		return (0);
	tmp = curr_p->cmds;
	while (tmp)
	{
		if (iterate_cmd_count_cat(ms, &tmp) == 1)
			break ;
		tmp = tmp->next;
	}
	if (ms->is_cat_sequence)
		(*curr_cmd) = tmp;
	return (0);
}

void	exec_cat_ls_sc(t_ms *ms)
{
	char	*input;

	while (ms->is_cat_sequence && ms->fake_cat_input-- > 0)
	{
		input = get_next_line(0);
		ft_free_ptr((void *) &input);
	}
}
