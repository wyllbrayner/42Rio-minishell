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

void ft_init_cmd(t_minishell *sh)
{
    printf("Dentro da init cmd -> Início\n");
    printf("line->: %s\n", sh->line);
    long i;
    long start;
    long len;
    long dquote;
    long squote;

// exit | echo -n "''cat |o|.c '|' cat > |o|.c e test de envio''"

// ls -la Makefile libminishell | exit
    i = 0;
    start = i;
    dquote = 0;
    squote = 0;
    while (sh->line[i])
    {
        while (sh->line[i])
        {
            if (sh->line[i] == '\'')
                squote++;
            else if (sh->line[i] == '\"')
                dquote++;
            else if (sh->line[i] == '|' && !(squote % 2) && !(dquote % 2))
                break ;
            i++;
        }
        len = (i - start);
        sh->tmp0 = ft_substr(sh->line, start, len);
        ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
        ft_free_minishell_single_aux(sh->tmp0);
//        sh->tmp0 = NULL;
        ft_print_list(sh);
//        ft_print_rev_list(sh);
        if (sh->line[i] == '|')
        {
            sh->tmp0 = ft_strdup("|");
            ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
            ft_free_minishell_single_aux(sh->tmp0);
            ft_print_list(sh);
            i++;
            start = i;
        }
    }



    printf("Dentro da init cmd -> Fim\n");
}
