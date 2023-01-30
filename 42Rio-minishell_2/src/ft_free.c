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

void ft_free_minishell_single_aux(char *str)
{
    printf("Dentro da free minishell single aux | inicio\n");
    if (str)
    {
//        printf("Dentro da free minishell single aux | vai liberar o ponteiro\n");
        free(str);
        str = NULL;
//        printf("Dentro da free minishell single aux | liberou     o ponteiro\n");
    }
    printf("Dentro da free minishell single aux | fim\n");
}

void ft_free_minishell_double_aux(char **str_double)
{
    long    i;
    printf("Dentro da free minishell double aux | inicio\n");
    i = 0;
    if (str_double)
    {
        while (str_double[i])
        {
//            printf("Dentro da free minishell double aux | dentro do loop | vai chamar a single\n");
            ft_free_minishell_single_aux(str_double[i]);
//            printf("Dentro da free minishell double aux | dentro do loop | retornou  da single\n");
            i++;
        }
//        printf("Dentro da free minishell double aux | fora do loop | vai liberar o ponteiro de ponteiro\n");
        free(str_double);
        str_double = NULL;
//        printf("Dentro da free minishell double aux | fora do loop | liberou o ponteiro de ponteiro\n");
    }
    printf("Dentro da free minishell double aux | fim\n");
}

static void ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
    long i;

    i = 0;
    if (file_fd)
    {
        while (i < amount_fd)
        {
            close(file_fd[i]);
            i++;
        }
        free(file_fd);
        file_fd = NULL;
    }
}

void ft_free_minishell(t_minishell *sh, int status)
{
    t_list *tmp;

    if (sh && (status == 1))
    {
        tmp = sh->lstcmd;
        printf("Dentro da free_minishell | chama     a single  para a line\n");
        ft_free_minishell_single_aux(sh->line);
        printf("Dentro da free_minishell | retorno da single  para a line\n");
        printf("Dentro da free_minishell | chama     a double para a parse_str\n");
        ft_free_minishell_double_aux(sh->parse_str);
        printf("Dentro da free_minishell | retorno  da double para a parse_str\n");
        printf("Dentro da free_minishell | chama     a double para a out_redirect_file\n");
        ft_free_minishell_double_aux(sh->out_redirect_file);
        printf("Dentro da free_minishell | retorno  da double para a out_redirect_file\n");
        printf("Dentro da free_minishell | chama   a close_fd para a out_redirect_file_fd\n");
        ft_free_minishell_close_fd(sh->out_redirect_file_fd, sh->out_redirect_file_fd_amount);
        printf("Dentro da free_minishell | retorno da close_fd para a out_redirect_file_fd\n");
        printf("Dentro da free_minishell | chama     a double para a  in_redirect_file\n");
        ft_free_minishell_double_aux(sh->in_redirect_file);
        printf("Dentro da free_minishell | retorno  da double para a  in_redirect_file\n");
        printf("Dentro da free_minishell | chama   a close_fd para a  in_redirect_file_fd\n");
        ft_free_minishell_close_fd(sh->in_redirect_file_fd, sh->in_redirect_file_fd_amount);
        printf("Dentro da free_minishell | retorno da close_fd para a  in_redirect_file_fd\n");
        printf("Dentro da free_minishell | chama a list destroy\n");
        ft_list_destroy(&tmp);
        printf("Dentro da free_minishell | retorno da list destroy\n");
        sh->out_redirect = 0;
        sh->in_redirect = 0;
        sh->s_int = 0;
    }
    if (sh && (status == 2))
    {
        printf("Dentro da free_minishell | chama     a double para a env\n");
        ft_free_minishell_double_aux(sh->env);
        printf("Dentro da free_minishell | retorno  da double para a env\n");
        printf("Dentro da free_minishell | chama     a double para a path\n");
        ft_free_minishell_double_aux(sh->path);
        printf("Dentro da free_minishell | free na tmp\n");
        if (tmp != NULL)
        {
            printf("Dentro da free_minishell | dentro do if free na tmp\n");
            free(tmp);
            tmp = NULL;
            printf("Dentro da free_minishell | dentro do if após free na tmp\n");
        }
        printf("Dentro da free_minishell | retorno  da free na tmp\n");
    }
}