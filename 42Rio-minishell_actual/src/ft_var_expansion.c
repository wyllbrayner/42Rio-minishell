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

void    ft_variable_expansion_aux(t_minishell *sh, t_node *node);

void ft_variable_expansion(t_minishell *sh)
{
    t_node *tmp;
    printf("Dentro da expansão de variáveis - Início\n");
    tmp = sh->head;
    while (tmp)
    {
        if (ft_strchr_i(tmp->cmd[0], '$') != 0)
        {
            printf("Nó: %s     possui %c\n", tmp->cmd[0], '$');
            ft_variable_expansion_aux(sh, tmp);
        }
        else
        {
            printf("Nó: %s não possui %c\n", tmp->cmd[0], '$');
        }
        tmp = tmp->next;
    }
    printf("Dentro da expansão de variáveis - Fim\n");
}

void    ft_variable_expansion_aux(t_minishell *sh, t_node *node)
{
    long    var[4];
    long    len;
    long    caract;

    printf("Dentro da expansão de variáveis_aux - Início\n");
    var[0] = ft_strchr_i(node->token, '$');
    if (var[0])
    {
        var[1] = ft_strlen(node->token);
        sh->tmp1 = ft_substr(node->token, (var[0] + 1), (var[1] - var[0] - 1));
        sh->tmp2 = ft_strjoin(sh->tmp1, "=");
//        printf("sh->tmp2: %s\n", sh->tmp2);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        sh->tmp1 = sh->tmp2;
        sh->tmp2 = NULL;
        var[3] = FALSE;
        ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        if (var[3])
        {
//            printf("var[3]: %ld | var[2](i): %ld | env: %s\n", var[3], var[2], sh->env[var[2]]);
            len = ((var[0] + (ft_strlen(sh->env[var[2]]) - ft_strchr_i(sh->env[var[2]], '='))));
            sh->tmp1 = (char *)malloc(sizeof(char) * len);
            if (!sh->tmp1)
            {
                printf("Não Mallocou\n");
                sh->ret = -3;
                return;
            }
            else
            {
//                printf("Mallocou %ld posições\n", len);
                sh->tmp1[--len] = '\0';
                ft_strlcpy(sh->tmp1, node->token, (var[0] + 1));
                printf("sh->tmp1 ( antes): %s#\n", sh->tmp1);
                caract = ft_strchr_i(sh->env[var[2]], '=');
//                printf("sh->env[%ld]: %s | caract: %ld\n", var[2], sh->env[var[2]], caract);
                ft_strlcpy(sh->tmp1+(var[0]), sh->env[var[2]]+(caract + 1), ft_strlen(sh->env[var[2]]) - caract);
                printf("sh->tmp1 (depois): %s\n", sh->tmp1);
            }
        }
        else
            printf("Faça alguma coisa\n");
        printf("Dentro da expansão de variáveis_aux - Fim\n");
    }
}


/*
static void    ft_variable_expansion_aux(t_minishell *sh, t_node *no)
{
    long    var[4];
    long    len;
    long    caract;

    printf("Dentro da expansão de variáveis_aux - Início\n");
    var[0] = ft_strchr_i(no->cmd[0], '$');
    if (var[0])
    {
        var[1] = ft_strlen(no->cmd[0]);
        sh->tmp1 = ft_substr(no->cmd[0], (var[0] + 1), (var[1] - var[0] - 1));
        sh->tmp2 = ft_strjoin(sh->tmp1, "=");
        printf("sh->tmp2: %s\n", sh->tmp2);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        sh->tmp1 = sh->tmp2;
        sh->tmp2 = NULL;
        var[3] = FALSE;
        ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        if (var[3])
        {
            printf("var[3]: %ld | var[2](i): %ld | env: %s\n", var[3], var[2], sh->env[var[2]]);
            len = ((var[0] + (ft_strlen(sh->env[var[2]]) - ft_strchr_i(sh->env[var[2]], '='))));
            sh->tmp1 = (char *)malloc(sizeof(char) * len);
            if (!sh->tmp1)
            {
                printf("Não Mallocou\n");
                sh->ret = -3;
                return;
            }
            else
            {
                printf("Mallocou %ld posições\n", len);
                sh->tmp1[--len] = '\0';
                ft_strlcpy(sh->tmp1, no->cmd[0], (var[0] + 1));
                printf("sh->tmp1 ( antes): %s#\n", sh->tmp1);
                caract = ft_strchr_i(sh->env[var[2]], '=');
                printf("sh->env[%ld]: %s | caract: %ld\n", var[2], sh->env[var[2]], caract);
                ft_strlcpy(sh->tmp1+(var[0]), sh->env[var[2]]+(caract + 1), ft_strlen(sh->env[var[2]]) - caract);
                printf("sh->tmp1 (depois): %s\n", sh->tmp1);
            }
        }
        else
            printf("Faça alguma coisa\n");
        printf("Dentro da expansão de variáveis_aux - Fim\n");
    }
}
*/


