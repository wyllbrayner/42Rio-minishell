/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:37:30 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/27 11:37:32 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_in_quote(char c, t_mini *mini)
{
	if (c == S_QUOTE)
	{
		if (mini->is_open_s == 0 && mini->is_open_d == 0)
			mini->is_open_s = 1;
		else if (mini->is_open_s == 1)
		{
			mini->is_open_s = 0;
			mini->final_s = 1;
		}
	}
	if (c == D_QUOTE)
	{
		if (mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->is_open_d = 1;
		else if (mini->is_open_d == 1)
		{
			mini->is_open_d = 0;
			mini->final_d = 1;
		}
	}
}

int	is_redirect(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
