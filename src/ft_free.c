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
    if (str)
    {
        free(str);
        str = NULL;
    }
}

void ft_free_minishell_double_aux(char **str_double)
{
    long    i;

    i = 0;
    if (str_double)
    {
        while (str_double[i])
        {
            ft_free_minishell_single_aux(str_double[i]);
            i++;
        }
        free(str_double);
        str_double = NULL;
    }
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
    if (sh && (status == 1))
    {
        ft_free_minishell_single_aux(sh->line);
        ft_free_minishell_double_aux(sh->parse_str);
        ft_free_minishell_double_aux(sh->out_redirect_file);
        ft_free_minishell_close_fd(sh->out_redirect_file_fd, sh->out_redirect_file_fd_amount);
        ft_free_minishell_double_aux(sh->in_redirect_file);
        ft_free_minishell_close_fd(sh->in_redirect_file_fd, sh->in_redirect_file_fd_amount);
        sh->out_redirect = 0;
        sh->in_redirect = 0;
    }
    if (sh && (status == 2))
    {
        ft_free_minishell_double_aux(sh->env);
        ft_free_minishell_double_aux(sh->path);
    }
}
