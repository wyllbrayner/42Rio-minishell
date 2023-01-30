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

void ft_valid_empty_cmd(t_minishell *sh)
{
    printf("Dentro da empty_cmd | inicio\n");
    sh->tmp1 = ft_strtrim(sh->line, " ");
    if (!sh->tmp1)
    {

        printf("Dentro da empty_cmd | ret -3\n");    
        sh->ret = -3;
        return ;
    }
//    else if ((ft_strlen(sh->tmp1) == 0) || ((ft_strlen(sh->tmp1) == 1) && ft_isspace(sh->tmp1[0])))
    if ((ft_strlen(sh->tmp1) == 0))
    {
        printf("Dentro da empty_cmd | ret -8\n");    
        sh->ret = -8;
    }
    ft_free_minishell_single_aux(sh->tmp1);
    printf("Dentro da empty_cmd | fim\n");    
}

void ft_valid_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

    if (sh)
    {
    printf("Dentro da valid quotes | inicio\n");
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
            printf("Dentro da valid quotes | ret -5\n");
            sh->ret = -5;
        }
    printf("Dentro da valid quotes | fim\n");
    }
}

int ft_valid_command_aux(t_minishell *sh, char *cmd)
{
    if (sh && cmd)
    {
        if (ft_strncmp(cmd, "echo", 5) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "cd", 3) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }

        else if (ft_strncmp(cmd, "pwd", 4) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "export", 7) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "unset", 6) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "env", 4) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
        else if (ft_strncmp(cmd, "exit", 5) == 0)
        {
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
//        else if (ft_strchr("-<>|\"\'", cmd[0]))
//        {
//            printf("Dentro da ft_valid_command_aux | %s NÃO É COMANDO, MAS RETORNO SERÁ = 1\n", cmd);
//            return (1);
//        }
        else
        {
            sh->tmp1 = ft_access_command(cmd, sh->path);
            if (!sh->tmp1)
            {
//                printf("Dentro da ft_valid_command_aux | %s NEXISTE\n", cmd);
                return (0);
            }
            ft_free_minishell_single_aux(sh->tmp1);
//            printf("Dentro da ft_valid_command_aux | %s EXISTE\n", cmd);
            return (1);
        }
    }
//    printf("Dentro da ft_valid_command_aux | %s NEXISTE\n", cmd);
    return (0);
}

int ft_pipe_or_redirect(t_minishell *sh, long i)
{
    return (sh->parse_str[i][0] == '|' || sh->parse_str[i][0] == '<' || sh->parse_str[i][0] == '>');
}

int ft_valid_file(t_minishell *sh, long i)
{
    int fd;

    fd = open(sh->parse_str[i], O_WRONLY | O_CREAT, 0666);
    if (fd == -1)
        return (0);
    else
    {
        close(fd);
        return (1);
    }
}

/*
        if (!ft_valid_command_aux(sh, sh->parse_str[i]) || !ft_valid_file(sh, i))
        {
            sh->ret = -4;
            sh->erro = sh->parse_str[i];
            ft_free_minishell_double_aux(sh->tmp3);
            return ;
        }
*/

//  0   1        2             3 4 5    6        7 8 9      10      11 
// ls -la Makefile src/ft_main.c | | grep Makefile > > test1.c test2.c

void ft_valid_lexcal_cmd(t_minishell *sh)
{
    long    i;

    i = 0;
    sh->tmp3 = (char **)malloc(sizeof(char *) * 2);
    if (!sh->tmp3)
    {
        sh->ret = -3;
        return ;
    }
    sh->tmp3[0] = NULL;
    sh->tmp3[1] = NULL;
    while (sh->parse_str[i])
    {
        sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
        i++;
        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh, i))
        {
            sh->tmp1 = ft_strjoin(sh->tmp3[0], " ");
            sh->tmp2 = ft_strjoin(sh->tmp1, sh->parse_str[i]);
            if (!sh->tmp1 || !sh->tmp2)
            {
                ft_free_minishell_single_aux(sh->tmp1);
                ft_free_minishell_single_aux(sh->tmp2);
                ft_free_minishell_double_aux(sh->tmp3);
                sh->ret = -3;
                return ;
            }
            ft_free_minishell_single_aux(sh->tmp3[0]);
            sh->tmp3[0] = sh->tmp2;
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp2 = NULL;
            i++;
        }
        ft_list_add_last(sh->lstcmd, sh->tmp3);
        sh->tmp3[0] = NULL;
        if (sh->parse_str[i] && ft_pipe_or_redirect(sh, i))
        {
            sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
            ft_list_add_last(sh->lstcmd, sh->tmp3);
            sh->tmp3[0] = NULL;
        }
        if (sh->parse_str[i])
            i++;
    }
    ft_free_minishell_double_aux(sh->tmp3);
}

/*
        while (sh->parse_str[i])
        {
            printf("dentro de parse | sh->parse_str[%i]: %s\n", i, sh->parse_str[i]);
            i++;
        }
*/

void ft_print_list(const t_minishell *sh)
{
    t_node *p;

    p = sh->lstcmd->begin;
    printf("L -> begin -> \n");
    while (p != NULL)
    {
        printf(" %s -> ", p->cmd[0]);
        p = p->next;
    }
    printf(" NULL\n");
    if (sh->lstcmd->end == NULL)
        printf("L -> end == NULL\n");
    else
        printf("L -> end %s\n", p->cmd[0]);
    printf("Size: %zu\n", sh->lstcmd->size);
}

void ft_parse(t_minishell *sh)
{
    if (sh)
    {
    printf("Dentro da parse | inicio\n");
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_quotes(sh);
        if (sh->ret < 0)
            return ;
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            return ;
        }
        long i = 0;
        while (sh->parse_str[i])
        {
            printf("Dentro da parse | sh->parse_str[%ld]: %s\n", i, sh->parse_str[i]);
            i++;
        }
/*
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
            return ;
        ft_print_list(sh);
*/
    }
    else
        sh->ret = -1;
    printf("Dentro da parse | fim\n");
}
