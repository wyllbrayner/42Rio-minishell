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

static void ft_valid_redirect_flow_aux(t_minishell *sh, int c);

void ft_valid_redirect_out(t_minishell *sh)
{
    long    i;
    long    j;
    long    start;

    i = 0;
    start = 0;
    ft_valid_redirect_flow_aux(sh, '>');
    if (sh->ret < 0)
        return ;
    while (sh->line[i] && (sh->line[i] != '>'))
        i++;
    if (i == 0)
    {
        sh->ret = -8;
        return;
    }
    if (sh->line[i] == '>' && (ft_isspace(sh->line[i - 1])))
    {
        sh->out_redirect = 1;
        i++;
        if (sh->line[i] && (sh->line[i] == '>'))
        {
            sh->out_redirect = 2;
            i++;
        }
        if (sh->line[i] && (!ft_isspace(sh->line[i])))
        {
            sh->ret = -6;
            return ;
        }
        start = i;
        while (sh->line[i] && ((sh->line[i] != '|') && (sh->line[i] != '<')))
            i++;
        if (i > start)
        {
            sh->tmp1 = ft_substr(&sh->line[start], 0, (size_t)(i - (start)));
            sh->out_redirect_file = ft_split(sh->tmp1, ' ');
            ft_free_minishell_single_aux(sh->tmp1);
            if (!sh->out_redirect_file)
            {
                sh->ret = -3;
                return ;
            }
            else
            {
                while (sh->out_redirect_file[sh->out_redirect_file_fd_amount])
                    sh->out_redirect_file_fd_amount++;
                sh->out_redirect_file_fd = (int *)malloc(sizeof(int) * sh->out_redirect_file_fd_amount);
                if (!sh->out_redirect_file_fd)
                {
                    sh->ret = -3;
                    return ;
                }
                else
                {
                    j = 0;
                    while (sh->out_redirect_file[j])
                    {
                        if (sh->out_redirect == 1)
                        {
                            sh->out_redirect_file_fd[j] = open(sh->out_redirect_file[j], O_WRONLY | O_CREAT, 0666);
                            if (sh->out_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->out_redirect_file[j];
                                return ;
                            }
                        }
                        else
                        {
                            sh->out_redirect_file_fd[j] = open(sh->out_redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
                            if (sh->out_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->out_redirect_file[j];
                                return ;
                            }
                        }
                        j++;
                    }
                }
            }
        }
        else
            sh->ret = -6;
    }
}

void ft_valid_redirect_in(t_minishell *sh)
{
    long    i;
    long    j;
    long    start;

    i = 0;
    start = 0;
    ft_valid_redirect_flow_aux(sh, '<');
    if (sh-> ret < 0)
        return ;
    while (sh->line[i] && (sh->line[i] != '<'))
        i++;
    if (i == 0)
    {
        sh->ret = -8;
        return;
    }
    if (sh->line[i] == '<' && (ft_isspace(sh->line[i - 1])))
    {
        sh->in_redirect = 1;
        i++;
        if (sh->line[i] && (sh->line[i] == '<'))
        {
            sh->in_redirect = 2;
            i++;
        }
        if (sh->line[i] && (!ft_isspace(sh->line[i])))
        {
            sh->ret = -6;
            return ;
        }
        start = i;
        while (sh->line[i] && ((sh->line[i] != '|') && (sh->line[i] != '>')))
            i++;
        if (i > start)
        {   
            sh->tmp1 = ft_substr(&sh->line[start], 0, (size_t)(i - (start)));
            sh->in_redirect_file = ft_split(sh->tmp1, ' ');
            ft_free_minishell_single_aux(sh->tmp1);
            if (!sh->in_redirect_file)
            {
                sh->ret = -3;
                return ;
            }
            else
            {
                while (sh->in_redirect_file[sh->in_redirect_file_fd_amount])
                    sh->in_redirect_file_fd_amount++;
                sh->in_redirect_file_fd = (int *)malloc(sizeof(int) * sh->in_redirect_file_fd_amount);
                if (!sh->in_redirect_file_fd)
                {
                    sh->ret = -3;
                    return ;
                }
                else
                {
                    j = 0;
                    while (sh->in_redirect_file[j])
                    {
                        if (sh->in_redirect == 1)
                        {
                            sh->in_redirect_file_fd[j] = open(sh->in_redirect_file[j], O_WRONLY | O_CREAT, 0666);
                            if (sh->in_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->in_redirect_file[j];
                                return ;
                            }
                        }
                        else
                        {
                            sh->in_redirect_file_fd[j] = open(sh->in_redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
                            if (sh->in_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->in_redirect_file[j];
                                return ;
                            }
                        }
                        j++;
                    }
                }
            }
        }
        else
            sh->ret = -6;
    }
}

static void ft_valid_redirect_flow_aux(t_minishell *sh, int c)
{
    long    i;
    long    count;

    i = 0;
    count = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == c)
        {
            count++;
            if ((count == 2) && (sh->line[i - 1] != c))
            {
                sh->ret = -6;
                return ;
            }
        }
        i++;
    }
    if (count > 2)
        sh->ret = -6;
}
