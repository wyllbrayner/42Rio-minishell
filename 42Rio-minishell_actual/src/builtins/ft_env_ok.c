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

void ft_builtin_env(t_minishell *sh, t_node *node)
{
    long    j;

//    printf("node->cmd[0]: %s | node->cmd[1]: %s\n", node->cmd[0], node->cmd[1]);
    if (node->cmd[1])
    {
        sh->ret = -7;
        sh->erro = node->cmd[1];
        sh->errnbr = 127;
    }
    else
    {
        j = 0;
        while (sh->env[j] && sh->s_int)
        {
            printf("%s\n", sh->env[j]);
            j++;
        }
//    	printf("\033[0m");
    }
}
