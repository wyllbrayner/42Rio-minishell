/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:21:29 by jodiniz           #+#    #+#             */
/*   Updated: 2023/01/20 10:21:29 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"

void ft_builtin_pwd(t_minishell *sh)
{
    printf("ta vindo pra ca msm\n");
    sh->tmp1 = getcwd(NULL, 0);
    ft_putendl_fd(sh->tmp1, 1);
    ft_free_minishell_single_aux(sh->tmp1);
}

/*
void ft_builtin_pwd(void)
{
    char    *tmp;

//    printf("ta vindo pra ca msm\n");
    tmp = getcwd(NULL, 0);
    ft_putendl_fd(tmp, 1);
    ft_free_minishell_single_aux(tmp);
	//free(tmp);
    //return (0);
}
*/