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
        add_history(sh->line);
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_amount_of_quotes(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect(sh);
        if (sh->ret < 0)
            return ;
        ft_cmd_builder(sh);
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
        ft_print_list(sh);
//        ft_print_rev_list(sh);
        ft_interpreter(sh);
        if (sh->ret < 0)
            return ;
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
    long    squote;
    long    dquote;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    i = 0;
    squote = 0;
    dquote = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == '\'')
            squote++;
        else if (sh->line[i] == '\"')
            dquote++;
        i++;
    }
    if (!ft_valid_quote(squote, dquote))
        sh->ret = -5;
//    printf("Dentro da ft_valid_quotes | fim\n");
}

void    ft_valid_redirect(t_minishell *sh)
{
//    printf("Dentro da valid_redirect -> Início\n");
    long var[5];

//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
    ft_cmd_builder_init_var(sh->caract, "><", var);
    while (sh->line[var[0]])
    {
//        printf("Dentro da valid_redirect -> loop\n");
        ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
//        printf("Dentro da valid_redirect -> loop após aux_0 var[0]: %ld\n", var[0]);
        if (ft_strchr("<>", sh->line[var[0]]) && (ft_strlen(sh->line) - var[0]) >= 3)
        {
            if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
            {
//                printf("Dentro da valid_redirect -> 1° if\n");
                sh->ret = -6;
                sh->erro = ">>>";
                return ;
            }
            else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
            {
//                printf("Dentro da valid_redirect -> 2° if\n");
                sh->ret = -6;
                sh->erro = "<<<";
                return ;
            }
            var[0]++;
        }
    }
//    printf("Dentro da valid_redirect -> Fim\n");
}

void ft_valid_lexcal_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_lexcal_cmd -> Início\n");
    t_node  *tmp;

    tmp = sh->head;
    sh->ret = -6;
    sh->erro ="|"; 
    while (tmp)
    {
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
            return ;
        if ((!tmp->next) && (tmp->cmd[0][0] == '|'))
            return ;
        if ((tmp->cmd[0][0] == '|') && (tmp->next))
        {
            if (!tmp->next->cmd[0])
                return ;
            if (tmp->next->cmd[0][0] == '|')
                return ;
        }
        tmp = tmp->next;
    }
    sh->ret = 0;
    sh->erro = NULL;
//    printf("Dentro da ft_valid_lexcal_cmd -> Fim\n");
}