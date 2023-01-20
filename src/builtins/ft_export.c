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

#include "../../header/ft_minishell.h"

void ft_builtin_export(t_minishell *sh, long i)
{
    long    j;
    char    tmp1[8192];
//    char    tmp2[8192];

    j = 0;
    printf("sh->parse_str[i]:   %s\n", sh->parse_str[i]);
    printf("sh->parse_str[i]:   %s\n", sh->parse_str[i + 1]);
    printf("tmp1 antes de bzero: %s\n", tmp1);
    ft_bzero(tmp1, 8192);
    printf("tmp1  após de bzero: %s\n", tmp1);
    if ( sh->parse_str[i + 1] && (ft_strchr(sh->parse_str[i + 1], '=')))
    {
        printf("Achou\n");
        while (sh->env[j])
        {
            printf("%s\n", sh->env[j]);
            j++;
        }
    }
}
