/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:51:51 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_free_history(t_ms *ms)
{
	t_history	*head;

	head = ms_last_history(ms->history);
	if (!head)
		return ;
	while (head)
	{
		ft_free_ptr((void *) &head->line);
		ft_free_ptr((void *) &head->next);
		head = head->prev;
	}
	ft_free_ptr((void *) &ms->history->line);
	ft_free_ptr((void *) &ms->history);
}
