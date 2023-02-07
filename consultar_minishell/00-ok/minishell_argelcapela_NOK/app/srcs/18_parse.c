/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/17 17:09:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_parse(t_ms *ms)
{
	t_p		*curr_p;
	int		i;

	curr_p = parse_prompts(ms);
	i = -1;
	while (++i < ms->p_amount)
	{
		curr_p = ms_get_prompt(ms, curr_p, i);
		curr_p->n_cmds = ft_mtx_size((void **) \
curr_p->this_p_line_splited_by_pipe);
		curr_p->index = i;
		if (ms_parse_commands (ms, curr_p))
			return (1);
	}
	return (0);
}
