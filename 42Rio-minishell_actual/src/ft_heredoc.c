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

void    ft_heredoc_build_list(t_minishell *sh, t_node *node)
{
    printf("ft_heredoc_build_list - Inicio\n");
    sh->tmp0 = readline("(42Rio) > ");
    if (sh->tmp0)
    {
        while(ft_strncmp(sh->tmp0, node->token, (ft_strlen(node->token) + 1)) != 0)
        {
            sh->tmp1 = ft_strjoin(sh->tmp0, "\n");
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
            if (!sh->tmp1)
            {
                sh->ret = -3;
                return ;
            }
            sh->tmp0 = ft_strjoin(" ", sh->tmp1);
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp1 = NULL;
            if (!sh->tmp0)
            {
                sh->ret = -3;
                return ;
            }
            ft_list_add_last(&sh->head_tmp, ft_node_create(sh->tmp0));
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
            sh->tmp0 = readline("(42Rio) > ");
        }
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
    }
    else
    {
        sh->ret = -3;
        return ;
    }
    printf("ft_heredoc_build_list - Fim\n");
}
void    ft_heredoc_expand_var(t_minishell *sh)
{
    printf("ft_heredoc_expand_var - Início\n");
    sh->ret = 0;
    t_node *node;

    node = sh->head_tmp;
    while (node)
    {
//        printf("token de heredoc pré expand_var: %s\n", node->token);
        if (!ft_strchr(node->token, '~'))
        {
            ft_expand_variable(sh, node);
//            printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
            if (sh->tmp5)
            {
//                printf("token de heredoc tmp5: %s\n", sh->tmp5);
                sh->tmp2 = ft_substr(sh->tmp5, 1, (ft_strlen(sh->tmp5) - 1));
                ft_free_minishell_single_aux(sh->tmp5);
                sh->tmp5 = NULL;
                if (!sh->tmp2)
                {
                    sh->ret = -3;
                    return ;
                }
                sh->tmp1 = sh->tmp2;
                sh->tmp2 = (void *)0;
                ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
            }
        }
//        printf("token de heredoc pós expand_var: %s\n", node->token);
        node = node->next;
    }
/*
*/
    printf("ft_heredoc_expand_var - Fim\n");
}

void    ft_heredoc_builder(t_minishell *sh, t_node *node)
{
    printf("ft_heredoc - Inicio\n");
    sh->head_tmp = (void *)0;
    ft_heredoc_build_list(sh, node);
    if (sh->ret < 0)
        return ;
    ft_heredoc_expand_var(sh);
    if (sh->ret < 0)
        return ;
    ft_print_list(sh->head_tmp);
    ft_list_destroy(&sh->head_tmp); /// pensar quando e onde devo destruir a lista!!!
    sh->head_tmp = (void *)0;
    printf("ft_heredoc - Fim\n");
}
