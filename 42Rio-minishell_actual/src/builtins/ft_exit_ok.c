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

static int ft_exit_return(int nbr)
{
    int i;
    int total;

    i = 0;
    total = 0;
    nbr = nbr * (-1);
    while (total <= nbr)
    {
        total = (i * 256);
        i++;
    }
    return (total - nbr);
}

void ft_builtin_exit(t_minishell *sh, t_node *node)
{
//    printf("Dentro da exit - Início\n");
    long i;

    i = 0;
    while (node->cmd[i])
        i++;
    if (!node->prev && !node->next)
    {
        ft_putendl_fd("exit", STDOUT_FILENO);
        sh->running = FALSE;
    }
    if (i >= 3)
    {
        sh->ret = -9;
        sh->erro = node->cmd[0];
        sh->errnbr = 1;
        sh->running = TRUE;
//        printf("errnbr: %i\n", sh->errnbr);
    }
    else if (i == 2)
    {
        i = 0;
        while (node->cmd[1][i])
        {
            if (!ft_strchr("+-0123456789", node->cmd[1][i]))
            {
                sh->ret = -11;
                sh->erro = node->cmd[1];
                sh->errnbr = 255;
//                printf("errnbr: %i\n", sh->errnbr);
                return ;
            }
            i++;
        }
        sh->errnbr = ft_atoi(node->cmd[1]);
        if (sh->errnbr >= 0)
            sh->errnbr = sh->errnbr % 256;
        else
            sh->errnbr = ft_exit_return(sh->errnbr);
//        printf("errnbr: %i\n", sh->errnbr);
    }
    else
    {
        sh->errnbr = 0;
//        printf("errnbr: %i\n", sh->errnbr);
    }
//    printf("errnbr: %i\n", sh->errnbr);
//    printf("Dentro da exit - Fim\n");
}
