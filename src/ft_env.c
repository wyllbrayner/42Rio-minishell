/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

void	ft_builtin_env(t_minishell *sh, t_node *node)
{
	long	j;

	if (node->cmd[1])
	{
		sh->ret = -7;
		sh->erro = node->cmd[1];
		g_sig.errnbr = 127;
	}
	else
	{
		j = 0;
		while (sh->env[j])
		{
			printf("%s\n", sh->env[j]);
			j++;
		}
		if (g_sig.s_int == 1)
			g_sig.errnbr = 0;
	}
}
