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
/*
        int i = 0;
        while (sh->parse_str[i])
        {
            printf("%s\n", sh->parse_str[i]);
            i++;
        }
*/
        ft_put_cmd_in_lst(sh);
        if (sh->ret < 0)
            return ;
//        ft_print_list(sh);
//        ft_print_rev_list(sh);
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a lexcal_cmd ret: %d\n", sh->ret);
/*
        ft_variable_expansion(sh);
        if (sh->ret < 0)
            return ;
*/
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim\n");
}

void ft_valid_empty_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_empty_cmd | inicio\n");
    sh->tmp1 = ft_strtrim(sh->line, " ");
    if (!sh->tmp1)
    {
        sh->ret = -3;
        return ;
    }
    if ((ft_strlen(sh->tmp1) == 0))
    {
        sh->ret = -8;
    }
    ft_free_minishell_single_aux(sh->tmp1);
    sh->tmp1 = NULL;
//    printf("Dentro da ft_valid_empty_cmd | fim\n");
}

void ft_valid_amount_of_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    if (sh)
    {
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
        {
            sh->ret = -5;
        }
    }
//    printf("Dentro da ft_valid_quotes | fim\n");
}

static void ft_count_quotes(char *cmd, long *dq)
{
    long    i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '\"')
            *dq = *dq + 1;
        i++;
    }
}

static int ft_pipe_or_redirect(char *cmd, long *dq)
{
    long i;

//    printf("Dentro da ft_pipe_or_redirect cmd: %s ; *dq: %ld - Início\n", cmd, *dq);
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '|' && ((*dq % 2) == 0))
        {
//            printf("para cmd: %s ; cmd[%li]: %c ; *dq: %ld ; resto: %ld = Retorno 1\n", cmd, i, cmd[i], *dq, (*dq % 2));
            return (1);
        }
        i++;
    }
//    printf("Dentro da ft_pipe_or_redirect cmd: %s ; *dq: %ld - Fim\n", cmd, *dq);
    return (0);
//    return (cmd[0] == '|');
//    return (cmd[0] == '|' || cmd[0] == '<' || cmd[0] == '>');
}

void ft_put_cmd_in_lst(t_minishell *sh)
{
    long    i;
    long    dq;

//    printf("Dentro da put cmd in list | inicio\n");
//     0 1   2  3        4 5    6    7     8 9  10 11    12"
//    cd | cat -e Makefile | echo "cat |o|.c | cat  > |o|.c"
    i = 0;
    dq = 0;
    while (sh->parse_str[i])
    {
        sh->tmp0 = ft_strdup(sh->parse_str[i]);
        ft_count_quotes(sh->parse_str[i], &dq);
//      testar se sh->tmp0 é null
        i++;
        if (sh->parse_str[i])
            ft_count_quotes(sh->parse_str[i], &dq);
        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh->parse_str[i], &dq))
        {
            sh->tmp1 = ft_strjoin(sh->tmp0, " ");
            sh->tmp2 = ft_strjoin(sh->tmp1, sh->parse_str[i]);
            if (!sh->tmp1 || !sh->tmp2)
            {
                ft_free_minishell_single_aux(sh->tmp0);
                sh->tmp0 = NULL;
                ft_free_minishell_single_aux(sh->tmp1);
                sh->tmp1 = NULL;
                ft_free_minishell_single_aux(sh->tmp2);
                sh->tmp2 = NULL;
                sh->ret = -3;
                return ;
            }
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = sh->tmp2;
            sh->tmp2 = NULL;
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp1 = NULL;
            i++;
//            if (sh->parse_str[i])
//                ft_count_quotes(sh->parse_str[i], &dq);
        }
        ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        if (sh->parse_str[i] && ft_pipe_or_redirect(sh->parse_str[i], &dq))
        {
            sh->tmp0 = ft_strdup(sh->parse_str[i]);
            ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
        }
        if (sh->parse_str[i])
            i++;
    }
//    printf("Dentro da put cmd in list | fim\n");
}

/*
void ft_put_cmd_in_lst(t_minishell *sh)
{
    long    i;

//    printf("Dentro da put cmd in list | inicio\n");
    i = 0;
    while (sh->parse_str[i])
    {
        sh->tmp0 = ft_strdup(sh->parse_str[i]);
//      testar se sh->tmp0 é null
        i++;
        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp1 = ft_strjoin(sh->tmp0, " ");
            sh->tmp2 = ft_strjoin(sh->tmp1, sh->parse_str[i]);
            if (!sh->tmp1 || !sh->tmp2)
            {
                ft_free_minishell_single_aux(sh->tmp0);
                sh->tmp0 = NULL;
                ft_free_minishell_single_aux(sh->tmp1);
                sh->tmp1 = NULL;
                ft_free_minishell_single_aux(sh->tmp2);
                sh->tmp2 = NULL;
                sh->ret = -3;
                return ;
            }
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = sh->tmp2;
            sh->tmp2 = NULL;
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp1 = NULL;
            i++;
        }
        ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        if (sh->parse_str[i] && ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp0 = ft_strdup(sh->parse_str[i]);
            ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
        }
        if (sh->parse_str[i])
            i++;
    }
//    printf("Dentro da put cmd in list | fim\n");
}
*/

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