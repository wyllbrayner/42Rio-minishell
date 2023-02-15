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



void ft_builtin_export(t_minishell *sh, t_node *node)
{
    long    count = 0;
    printf("node->token: %s\n", node->token);
    while (node->cmd[count])
    {
        printf("node->cmd[%ld]: %s\n", count, node->cmd[count]);
        count++;
    }
    long    start;
    long    end;
    long    i;
    long    status;

    printf("Dentro da export\n");

//    start = ft_strchr_i(node->token, ' ');
    start = 0;
    end = ft_strchr_i(node->cmd[1], '=');
    printf("node->cmd[1]: %s | start %ld | end: %ld\n", node->cmd[1], start, end);
    if (end > start)
    {
        sh->tmp1 = ft_substr(node->cmd[1], start, end - start);
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
        if (status)
        {
            printf("    Achei a variável de ambiente: %s em env[%ld]: %s\n", sh->tmp1, i, sh->env[i]);
            ft_free_minishell_single_aux(sh->env[i]);
            sh->env[i] = NULL;
            sh->env[i] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1])); //
//            sh->env[i] = ft_substr(node->cmd[1], (end + 1), (ft_strlen(node->cmd[1]) - (end + 1))); //
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
//            sh->tmp3[--i] = ft_substr(node->cmd[1], (end + 1), (ft_strlen(node->cmd[1]) - (end + 1))); //
            sh->tmp3[--i] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1])); //
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
        sh->tmp3 = NULL; // colocar após a linha 70!!!!
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


/*
void ft_builtin_export(t_minishell *sh, t_node *node)
{
    long    start;
    long    end;
    long    i;
    long    status;

    printf("Dentro da export\n");

    start = ft_strchr_i(node->token, ' ');
    end = ft_strchr_i(node->token, '=');
    printf("node->token: %s | start %ld | end: %ld\n", node->token, start, end);
    if (end > start)
    {
        sh->tmp1 = ft_substr(node->token, (start + 1), end - start);
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
        if (status)
        {
            printf("    Achei a variável de ambiente: %s em env[%ld]: %s\n", sh->tmp1, i, sh->env[i]);
            ft_free_minishell_single_aux(sh->env[i]);
            sh->env[i] = NULL;
            sh->env[i] = ft_substr(node->token, (start + 1), (ft_strlen(node->token) - start));
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
            sh->tmp3[--i] = ft_substr(node->token, (start + 1), (ft_strlen(node->token) - start));
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
        sh->tmp3 = NULL; // colocar após a linha 70!!!!
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
*/
