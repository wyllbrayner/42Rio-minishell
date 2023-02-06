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

void ft_builtin_unset(t_minishell *sh)
{
    long    start;
    long    end;
    long    i;
    int     status;

    printf("Dentro da unset\n");
    start = ft_strchr_i(sh->head->cmd[0], ' ');
    if (start != 0)
    {
        end = ft_strlen(sh->head->cmd[0]);
        sh->tmp1 = ft_substr(sh->head->cmd[0], (start + 1), (end - start - 1));
//        printf("Dentro da unset | start: %ld | end: %ld | sub_str: %s\n", start, end, sh->tmp1);
        sh->tmp2 = ft_strjoin(sh->tmp1, "=");
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        sh->tmp1 = sh->tmp2;
        sh->tmp2 = NULL;
        i = 0;
        status = FALSE;
        while (sh->env[i])
        {
//            printf("Dentro do loop: sh->env[%ld]: %s | sh->tmp1: %s | end: %ld | start: %ld\n", i, sh->env[i], sh->tmp1, (end), start);
            if (ft_strncmp(sh->env[i], sh->tmp1, ((end) - start)) == 0)
            {
                status = TRUE;
                break ;
            }
            i++;
        }
        if (status)
        {
            printf("    Achei a variável de ambiente: %s em env[%ld]: %s\n", sh->tmp1, i, sh->env[i]);
        }
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
    }
    else
        printf("Apenas unset | Apagar esta mensagem !!!\n");
}
