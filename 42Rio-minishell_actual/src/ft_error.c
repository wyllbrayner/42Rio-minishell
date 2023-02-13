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

void    ft_minishell_error(t_minishell *sh)
{
    if (sh)
    {
        if (sh->ret == -1)
            printf("(Minishell): Erro inesperado!\n");
        else if (sh->ret == -2)
            printf("(Minishell): %s: No such file or directory\n", sh->erro);
        else if (sh->ret == -3)
            printf("malloc retornou error\n");
        else if (sh->ret == -4)
            printf("(Minishell): %s: command not found\n", sh->erro);
        else if (sh->ret == -5)
            printf("(Minishell): Error: unclosed quotes\n");
        else if (sh->ret == -6)
        {
            if (!sh->erro)
                printf("(Minishell): syntax error near unexpected token `newline'\n");
            else
                printf("(Minishell): syntax error near unexpected token `%s'\n", sh->erro);
        }
        else if (sh->ret == -7)
            printf("(Minishell): %s: No such file or directory\n", sh->erro);
        else if (sh->ret == -8)
            ;
        else if (sh->ret == -9)
            printf("(Minishell): %s: too many arguments\n", sh->erro);
        sh->ret = 0;
        sh->erro = NULL;
    }
}
