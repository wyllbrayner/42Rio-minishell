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

void ft_valid_empty_cmd(t_minishell *sh);
void ft_valid_amount_of_quotes(t_minishell *sh);
void ft_put_cmd_in_lst(t_minishell *sh);
void ft_valid_lexcal_cmd(t_minishell *sh);

void ft_parse(t_minishell *sh)
{
//    printf("Dentro da parse | inicio\n");
    if (sh)
    {
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_amount_of_quotes(sh);
        if (sh->ret < 0)
            return ;
        ft_init_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a valid quotes ret: %d\n", sh->ret);
        ft_valid_redirect_out(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect_in(sh);
        if (sh->ret < 0)
            return ;
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            return ;
        }
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a lexcal_cmd ret: %d\n", sh->ret);
/*
        ft_variable_expansion(sh);
        if (sh->ret < 0)
            return ;
*/
        ft_print_list(sh);
        ft_print_rev_list(sh);
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim\n");
}

void ft_valid_empty_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_empty_cmd | inicio\n");
    sh->tmp0 = ft_strtrim(sh->line, " ");
    if (!sh->tmp0)
    {
        sh->ret = -3;
        return ;
    }
    if ((ft_strlen(sh->tmp0) == 0))
    {
        sh->ret = -8;
    }
    ft_free_minishell_single_aux(sh->line);
    sh->line = NULL;
    sh->line = sh->tmp0;
    sh->tmp0 = NULL;
//    ft_free_minishell_single_aux(sh->tmp1);
//    sh->tmp1 = NULL;
//    printf("Dentro da ft_valid_empty_cmd | fim\n");
}

void ft_valid_amount_of_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    i = 0;
    count_s = 0;
    count_d = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == '\'')
            count_s++;
        else if (sh->line[i] == '\"')
            count_d++;
        i++;
    }
    if (((count_s % 2) != 0) || ((count_d % 2) != 0))
        sh->ret = -5;
//    printf("Dentro da ft_valid_quotes | fim\n");
}

void ft_valid_lexcal_cmd(t_minishell *sh)
{
    t_node  *tmp;

    tmp = sh->head;
    while (tmp)
    {
//        printf("cmd[0] de tmp: %s\n", tmp->cmd[0]);
//        if (tmp->prev)
//        {
//            if (tmp->prev->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do prev\n");
//                sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->prev: %s\n", tmp->prev->cmd[0]);
//        }
//        if (tmp->next)
//        {
//            if (tmp->next->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do next\n");
//                sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->next: %s\n", tmp->next->cmd[0]);
//        }
//        sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//        sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro ="|"; 
            return ;
        }
        else if ((tmp->cmd[0][0] == '|') && (tmp->next) && (tmp->next->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro = "|";
            return ;
        }
//        else if ((tmp->cmd[0][0] == '|') && (sh->tmp3 && sh->tmp4))
//        {
//            if ((!ft_access_command(sh->tmp3[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp3[0];
//                return ;           
//            }
//            else if ((!ft_access_command(sh->tmp4[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp4[0];
//                return ;           
//            }
//        }
//        ft_free_minishell_double_aux(sh->tmp3);
//        ft_free_minishell_double_aux(sh->tmp4);
        tmp = tmp->next;
    }
}