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
            ft_putendl_fd("(Minishell): Erro inesperado!", 2);
        else if (sh->ret == -3)
            ;
        else if (sh->ret == -4)
            printf("(Minishell): %s: command not found\n", sh->erro);
        else if (sh->ret == -5)
            ft_putendl_fd("(Minishell): Error: unclosed quotes", 2);
        else if (sh->ret == -6)
        {
            if (!sh->erro)
                ft_putendl_fd("(Minishell): syntax error near unexpected token `newline'", 2);
            else
                printf("(Minishell): syntax error near unexpected token `%s'\n", sh->erro);
        }
        else if (sh->ret == -7)
            printf("(Minishell): %s: No such file or directory\n", sh->erro);
        else if (sh->ret == -8)
            ;
        else if (sh->ret == -9)
            printf("(Minishell): %s: too many arguments\n", sh->erro);
        else if (sh->ret == -10)
            printf("(Minishell): \'%s\': not a valid identifier\n", sh->erro);
        else if (sh->ret == -11)
            printf("(Minishell): %s: numeric argument required\n", sh->erro);
        sh->ret = 0;
        sh->erro = (void *)0;
    }
}
/// echo $?