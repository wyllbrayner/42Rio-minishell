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

/*
char *ft_join_path(char const *path, char const *cmd)
{
    char *tmp1;
    char *tmp2;

    tmp1 = NULL;
    tmp2 = NULL;
    tmp1 = ft_strjoin(path, "/");
    if (!tmp1)
        return (NULL);
    tmp2 = ft_strjoin(tmp1, cmd);
    if (!tmp2)
    {
        ft_free_minishell_single_aux(tmp1);
        return (NULL);
    }
    return(tmp2);
}
*/

void ft_valid_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

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
}

void ft_valid_out_redirect(t_minishell *sh)
{
    long    i;
    long    j;
    long    count;
    long    start;

    i = 0;
    start = 0;
    count = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == '>')
        {
            count++;
            if ((count == 2) && (sh->line[i - 1] != '>'))
            {
                printf("Dentro da ft_valid_out_redirect i: %ld count: %ld\n", i, count);
                sh->ret = -6;
                return ;
            }
        }
        i++;
    }
    if (count > 2)
    {
        sh->ret = -6;
        return ;
    }
    i = 0;
/*
*/
    while (sh->line[i] && (sh->line[i] != '>'))
        i++;
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
            sh->out_redirect_file = ft_split(ft_substr(&sh->line[start], 0, (size_t)(i - (start))), ' ');
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
                                sh->ret = -7;
                        }
                        else
                        {
                            sh->out_redirect_file_fd[j] = open(sh->out_redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
                            if (sh->out_redirect_file_fd[j] == -1)
                                sh->ret -7;
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

void ft_parse(t_minishell *sh)
{
    ft_valid_quotes(sh);
    if (sh->ret < 0)
        return ;
    ft_valid_out_redirect(sh);
    if (sh->ret < 0)
        return ;
/*
    ft_valid_in_redirect(sh);
    if (sh->ret < 0)
        return ;
    sh->parse_str = ft_split(sh->line, ' ');
    ft_parse_comand_is_valid(sh);
*/
}


/*
                    int c = 0;
                    while (sh->redirect_file[z])
                    {
                        printf("sh->redirett_file[%ld]: %s\n", z, sh->redirect_file[z]);
                        c = access(sh->redirect_file[z], F_OK & W_OK);
                        if (c == 0)
                            printf("Arquivo     exite e     temos acesso de escrita ao arquivo %s | c: %c\n", sh->redirect_file[z], c);
                        else
                            printf("Arquivo não exite e não temos acesso de escrita ao arquivo %s | c: %c\n", sh->redirect_file[z], c);
                        c = access(sh->redirect_file[z], F_OK);
                        if (c == 0)
                            printf("Arquivo     exite                     : %s | c: %i\n", sh->redirect_file[z], c);
                        else
                            printf("Arquivo não exite                     : %s | c: %i\n", sh->redirect_file[z], c);
                        c = access(sh->redirect_file[z], W_OK);
                        if (c == 0)
                            printf("    temos acesso de escrita ao arquivo: %s | c: %i\n", sh->redirect_file[z], c);
                        else
                            printf("Não temos acesso de escrita ao arquivo: %s | c: %i\n", sh->redirect_file[z], c);
                        z++;
                    }
*/
