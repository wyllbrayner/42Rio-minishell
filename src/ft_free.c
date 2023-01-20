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
        free(str);
    str = NULL;
}

static void ft_free_minishell_double_aux(char **str_double)
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

void ft_free_minishell(t_minishell *sh, int status)
{
    if (status == 1)
    {
        ft_free_minishell_double_aux(sh->parse_str);
        ft_free_minishell_single_aux(sh->line);
    }
    if (status == 2)
    {
        ft_free_minishell_double_aux(sh->path);
        ft_free_minishell_double_aux(sh->env);

//        ft_free_minishell_single_aux(sh->pwd);
    }
}
