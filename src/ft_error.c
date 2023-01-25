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
            printf("Erro inesperado!\n");
//        else if (sh->ret == -2)
//            printf("readline retornou nulo e o programa será encerrado agora!\n");
        else if (sh->ret == -3)
            printf("malloc retornou error\n");
        else if (sh->ret == -4)
            printf("(Minishell): %s: command not found\n", sh->erro);
        else if (sh->ret == -5)
            printf("Error: unclosed quotes\n");
        else if (sh->ret == -6)
            printf("(Minishell): syntax error near unexpected token `newline'\n");
        else if (sh->ret == -7)
            printf("(Minishell): %s: No such file or directory\n", sh->erro);
        else if (sh->ret == -8)
            ;
        sh->ret = 0;
        sh->erro = NULL;
    }
}

void    ft_select_way(t_minishell *sh)
{
    if (sh->parse_str)
    {
        if (ft_strncmp(sh->parse_str[0], "echo", 5) == 0)
            printf("Chamar a função builtin echo\n");
        else if (ft_strncmp(sh->parse_str[0], "cd", 3) == 0)
            printf("Chamar a função builtin cd\n");
        else if (ft_strncmp(sh->parse_str[0], "pwd", 4) == 0)
            printf("Chamar a função builtin pwd\n");
        else if (ft_strncmp(sh->parse_str[0], "export", 7) == 0)
            printf("Chamar a função builtin export\n");
        else if (ft_strncmp(sh->parse_str[0], "unset", 6) == 0)
            printf("Chamar a função builtin unset\n");
        else if (ft_strncmp(sh->parse_str[0], "env", 4) == 0)
            ft_builtin_env(sh);
        else if (ft_strncmp(sh->parse_str[0], "exit", 5) == 0)
            ft_builtin_exit(sh);
        else
        {
        /// JONATAS sugiro colocar sua função a partir daqui!!!
            int rato;
            rato = 0;
            ft_start_command(sh, &rato);
            wait(NULL);
    //        waitpid(rato, NULL, 0);
        }
    }
    else
        printf("sh->parse não inicializado\n");     
}