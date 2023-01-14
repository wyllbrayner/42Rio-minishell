/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:56:52 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/02 19:07:12 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static int	pipe_fd(t_p *prompt, int tmp_fd[])
{
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	return (tmp_fd[1]);
}

void	ms_print_history(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	t_history	*h;
	int			i;
	int			aux;
	int			tmp_fd[2];

	i = 1;
	h = ms->history;
	if ((curr_cmd->index == prompt->args_amount - 1) \
	&& prompt->output_fd > 0)
		aux = prompt->output_fd;
	else if (curr_cmd->index == prompt->args_amount - 1)
		aux = 1;
	else
		aux = pipe_fd(prompt, tmp_fd);
	while (h)
	{
		if (h->index != 0 && h->line != NULL)
			ft_printf_to_fd(aux, "  %d  %s", i, h->line);
		i++;
		h = h->next;
	}
}
