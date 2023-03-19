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

#include "../../header/ft_minishell.h"

extern t_signal	g_sig;

//    printf("Dentro de ft_builtin_env Início cmd[0]: %s | cmd[1]: %s \n", 
//	node->cmd[0], node->cmd[1]);
//        while (sh->env[j] && sh->s_int)
//    	printf("\033[0m");
//    printf("Dentro de ft_builtin_env Fim cmd[0]: %s | cmd[1]: %s \n", 
//	node->cmd[0], node->cmd[1]);
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
