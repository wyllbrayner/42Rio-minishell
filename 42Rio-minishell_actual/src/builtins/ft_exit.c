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

void ft_builtin_exit(t_minishell *sh, t_node *node)
{
    long i;

    i = 0;
    sh->errnbr = 0;
    while (node->cmd[i])
        i++;
    if (i >= 3)
    {
        sh->ret = -9;
        sh->erro = node->cmd[2];
        sh->errnbr = 1;
    }
    else
    {
        if (!node->prev && !node->next)
        {
//            printf("Dentro do if para ambos os ponteiros nulos | altera running para 0\n");
//            printf("%s\n", node->first_cmd);
            if (node->cmd[1])
            {
                i = 0;
                while (node->cmd[1][i])
                {
                    if (!ft_strchr("+-0123456789", node->cmd[1][i]))
                    {
                        sh->errnbr = 2;
                        return ;
                    }
                    i++;
                }
                sh->errnbr = (ft_atoi(node->cmd[1]) % 255);
            }
            sh->running = FALSE;
        }
//        else
//        {
//            printf("Dentro do if para ambos os ponteiros não nulos | mantem running como 1\n");
//        }
    }
}