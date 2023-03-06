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

// exit | echo -n "''cat |o|.c '|' cat > |o|.c e test de envio''"
// ls -la Makefile libminishell | exit


void    ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote);
static  void    ft_cmd_builder_aux_1(t_minishell *sh, char *cmd);

// 01234567
// ls > ser

void ft_cmd_builder(t_minishell *sh)
{
//    printf("Dentro da cmd builder-> Início\n");
//    printf("line->: %s\n", sh->line);
    long var[5];

//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
    ft_cmd_builder_init_var(sh->caract, "|><", var);
    while (sh->line[var[0]])
    {
        ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
        var[4] = (var[0] - var[1]);   // len = (i - start);
        if (var[4])
        {
            ft_cmd_builder_aux_1(sh, ft_substr(sh->line, var[1], var[4]));
            if (sh->ret < 0)
                return ;
        }
        if (sh->line[var[0]] == '|')
        {
            ft_cmd_builder_aux_1(sh, ft_strdup("|"));
            if (sh->ret < 0)
                return ;
            var[0]++;
        }
        else if (ft_strncmp(&sh->line[var[0]], "<<", 2) == 0)
        {
            ft_cmd_builder_aux_1(sh, ft_strdup("<<"));
            if (sh->ret < 0)
                return ;
            var[0] = var[0] + 2;
        }
        else if (ft_strncmp(&sh->line[var[0]], "<", 1) == 0)
        {
            ft_cmd_builder_aux_1(sh, ft_strdup("<"));
            if (sh->ret < 0)
                return ;
            var[0]++;
        }
        else if (ft_strncmp(&sh->line[var[0]], ">>", 2) == 0)
        {
            ft_cmd_builder_aux_1(sh, ft_strdup(">>"));
            if (sh->ret < 0)
                return ;
            var[0] = var[0] + 2;
        }
        else if (ft_strncmp(&sh->line[var[0]], ">", 1) == 0)
        {
            ft_cmd_builder_aux_1(sh, ft_strdup(">"));
            if (sh->ret < 0)
                return ;
            var[0]++;
        }
        var[1] = var[0];
        while (sh->line[var[0]] && (ft_strchr("><", sh->line[var[0]]))) //confirmar se ainda faz sentido manter este loop
            var[0]++; // idem do anterior
    }
    ft_bzero(sh->caract, (sizeof(char) * 4));
//    printf("Dentro da cmd builder -> Fim (ret: sh->ret: %i)\n", sh->ret);
}

void ft_cmd_builder_init_var(char *caract, char *str, long *var)
{
//    printf("Dentro da init var -> Início\n");
    ft_bzero(caract, (sizeof(char) * 4));
    var[0] = 0;
    var[1] = 0;
    var[2] = 0;
    var[3] = 0;
    ft_strlcpy(caract, str, (ft_strlen(str) + 1));
//    printf("Dentro da init var -> Fim\n");
}

// 01 ls
// || ls OK

// 012 ls
// | | ls NOK

// ls < do_ls_< | cat < doc_cat_< | ls >> doc_ls_>> | ls > doc_ls_>

void    ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote)
{
//    printf("Dentro da init cmd aux_0 -> Início (i: %li, sq: %li, dq: %ld, caract: %s)\n", *i, *squote, *dquote, sh->caract);
    while (sh->line[*i] && 
    (!((ft_strchr(sh->caract, sh->line[*i]) && ft_valid_quote(*squote, *dquote)))))
    {
        if (sh->line[*i] == '\'')
            *squote = *squote + 1;
        else if (sh->line[*i] == '\"')
            *dquote = *dquote + 1;
        *i = *i + 1;
    }
//    printf("Dentro da init cmd aux_0 -> Fim (i: %li, sq: %li, dq: %ld, caract: %s)\n", *i, *squote, *dquote, sh->caract);
}


//   | | ls NOK
static void    ft_cmd_builder_aux_1(t_minishell *sh, char *cmd)
{
//    printf("Dentro da init cmd aux_1 -> Início: cmd: #%s#\n", cmd);
    if (!cmd)
    {
        sh->ret = -3;
        return ;
    }
    sh->tmp0 = ft_strtrim(cmd, " ");
//    printf("Dentro da init cmd aux_1 -> Início: trim(cmd): #%s#\n", sh->tmp0);
    ft_free_minishell_single_aux(cmd);
    cmd = NULL;
    if (!sh->tmp0 || !*sh->tmp0)
    {
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -6;
        sh->erro = "|";
        return ;
    }
    ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
    ft_free_minishell_single_aux(sh->tmp0);
    sh->tmp0 = NULL;
//    ft_print_list(sh->head);
//    printf("Dentro da init cmd aux_1 -> Fim\n");
}
