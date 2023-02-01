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

void ft_valid_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

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
            sh->ret = -5;
    }
}

void ft_valid_redirect_flow_aux(t_minishell *sh, int c)
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

void ft_valid_redirect_out(t_minishell *sh)
{
    long    i;
    long    j;
    long    start;

    i = 0;
    start = 0;
    ft_valid_redirect_flow_aux(sh, '>');
    if (sh-> ret < 0)
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

/*
int ft_valid_command_aux(t_minishell *sh, char *cmd)
{
    if (sh && cmd)
    {
        if (ft_strncmp(cmd, "echo", 5) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "cd", 3) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }

        else if (ft_strncmp(cmd, "pwd", 4) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "export", 7) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "unset", 6) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "env", 4) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "exit", 5) == 0)
        {
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strchr("-<>|\"\'", cmd[0]))
        {
            printf("Dentro da ft_valid_command_aux | %s NÃO É COMANDO, MAS RETORNO SERÁ = 1\n", cmd);
            return (1);
        }
        else
        {
            sh->tmp1 = ft_access_command(cmd, sh->path);
            if (!sh->tmp1)
            {
                printf("Dentro da ft_valid_command_aux | %s NEXISTE\n", cmd);
                return (0);
            }
            ft_free_minishell_single_aux(sh->tmp1);
            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
    }
    printf("Dentro da ft_valid_command_aux | %s NEXISTE\n", cmd);
    return (0);
}

void ft_valid_comand(t_minishell *sh)
{
    long    i;

    i = 0;
    while (sh->parse_str[i])
    {
        if (!ft_valid_command_aux(sh, sh->parse_str[i]))
        {
            sh->ret = -4;
            sh->erro = sh->parse_str[i];
            return ;
        }
        i++;
    }
}
*/

void ft_valid_cmd(t_minishell *sh)
{
    sh->tmp1 = ft_strtrim(sh->line, " ");
    if (!sh->tmp1)
        sh->ret = -3;
    else if ((ft_strlen(sh->tmp1) == 0) || ((ft_strlen(sh->tmp1) == 1) && ft_isspace(sh->tmp1[0])))
        sh->ret = -8;
    ft_free_minishell_single_aux(sh->tmp1);
}

void ft_parse(t_minishell *sh)
{
    if (sh)
    {
        ft_valid_cmd(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_quotes(sh);
        if (sh->ret < 0)
            return ;
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
        ft_valid_comand(sh);
        if (sh->ret < 0)
            return ;
*/

    }
    else
        sh->ret = -1;
}

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
