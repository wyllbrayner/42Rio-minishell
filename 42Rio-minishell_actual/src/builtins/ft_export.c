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

void ft_builtin_export(t_minishell *sh)
{
    long    start;
    long    end;
    long    i;
    int     status;

    printf("Dentro da export\n");

    start = ft_strchr_i(sh->head->cmd[0], ' ');
    end = ft_strchr_i(sh->head->cmd[0], '=');
    if (end > start)
    {
        sh->tmp1 = ft_substr(sh->head->cmd[0], (start + 1), end - start);
        printf("Dentro da export | start: %ld | end: %ld | sub_str: %s\n", start, end, sh->tmp1);
        i = 0;
        status = FALSE;
        while (sh->env[i])
        {
            if (ft_strncmp(sh->env[i], sh->tmp1, (end - start)) == 0)
            {
                status = TRUE;
                break ;
            }
            i++;
        }
//      if (status == 1)
        if (status)
        {
            printf("    Achei a variável de ambiente: %s em env[%ld]: %s\n", sh->tmp1, i, sh->env[i]);
            ft_free_minishell_single_aux(sh->env[i]);
            sh->env[i] = NULL;
            sh->env[i] = ft_substr(sh->head->cmd[0], (start + 1), (ft_strlen(sh->head->cmd[0]) - start));
        }
        else
        {
            printf("Não achei a variável de ambiente: %s em env[%ld]: %s\n", sh->tmp1, i, sh->env[i]);
            printf("Total de variáveis de ambiente: %ld\n", i);
            i++;
            sh->tmp3 = (char **)malloc(sizeof(char *) * (++i));
            if (!sh->tmp3)
            {
                ft_free_minishell_single_aux(sh->tmp1);
                sh->ret = -3;
                return ;
            }
            sh->tmp3[--i] = NULL;
            sh->tmp3[--i] = ft_substr(sh->head->cmd[0], (start + 1), (ft_strlen(sh->head->cmd[0]) - start));
            while(--i >= 0)
            {
                sh->tmp3[i] = sh->env[i];
                sh->env[i] = NULL;
            }
            ft_free_minishell_double_aux(sh->env);
            sh->env = NULL;
            sh->env = sh->tmp3;
        }
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        sh->tmp3 = NULL;
        /*
        i = 0;
        while (sh->env[i])
        {
            printf("sh->env[%ld]: %s\n", i, sh->env[i]);
            i++;
        }
        */
    }
    else
    {
        i = 0;
        while (sh->env[i])
        {
            printf("declare -x %s\n", sh->env[i]);
            i++;
        }
    }
}
