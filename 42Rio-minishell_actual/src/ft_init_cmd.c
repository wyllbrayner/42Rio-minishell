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

static void    ft_init_cmd_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote);
static void    ft_init_cmd_aux_1(t_minishell *sh, char *cmd);

void ft_init_cmd(t_minishell *sh)
{
//    printf("Dentro da init cmd -> Início\n");
//    printf("line->: %s\n", sh->line);
    long var[5];

    var[0] = 0;         //    i = 0;
//    var[1] = var[0];         //    start = i;
    var[2] = 0;         //    dquote = 0;
    var[3] = 0;         //    squote = 0;
    while (sh->line[var[0]])
    {
        var[1] = var[0];         //    start = i;
        ft_init_cmd_aux_0(sh, &var[0], &var[3], &var[2]);
        var[4] = (var[0] - var[1]);   // len = (i - start);
        if (var[4])
        {
            ft_init_cmd_aux_1(sh, ft_substr(sh->line, var[1], var[4]));
            if (sh->ret < 0)
                return ;
        }
        if (sh->line[var[0]] == '|')
        {
            ft_init_cmd_aux_1(sh, ft_strdup("|"));
            if (sh->ret < 0)
                return ;
            var[1] = ++var[0];
        }
    }
//    printf("Dentro da init cmd -> Fim\n");
}
/*
*/
// 012345
// ls>ser
// 01 ls
// || ls OK

// 012 ls
// | | ls NOK
static void    ft_init_cmd_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote)
{
//    printf("Dentro da init cmd aux_0 -> Início\n");
//    while (sh->line[*i] && 
//                (!((sh->line[*i] == '|') && ft_valid_quote(*squote, *dquote))))
    while (sh->line[*i] && 
    (!((ft_strchr("|", sh->line[*i]) && ft_valid_quote(*squote, *dquote)))))
    {
        if (sh->line[*i] == '\'')
            *squote = *squote + 1;
        else if (sh->line[*i] == '\"')
            *dquote = *dquote + 1;
        *i = *i + 1;
    }
//    printf("Dentro da init cmd aux_0 -> Fim\n");
}


static void    ft_init_cmd_aux_1(t_minishell *sh, char *cmd)
{
//    printf("Dentro da init cmd aux_1 -> Início: cmd: #%s#\n", cmd);
    if (!cmd)
    {
        sh->ret = -3;
        return ;
    }
    sh->tmp0 = ft_strtrim(cmd, " ");
    ft_free_minishell_single_aux(cmd);
    cmd = NULL;
    if (!sh->tmp0)
    {
        sh->ret = -3;
        return ;
    }
    ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
    ft_free_minishell_single_aux(sh->tmp0);
    sh->tmp0 = NULL;
//    printf("Dentro da init cmd aux_1 -> Fim\n");
}

/*
void ft_init_cmd(t_minishell *sh)
{
    printf("Dentro da init cmd -> Início\n");
    printf("line->: %s\n", sh->line);
    long i;
    long start;
    long len;
    long dquote;
    long squote;

    i = 0;
    start = i;
    dquote = 0;
    squote = 0;
    len = 0; //temporário


    // 01 ls
    // || ls OK

    // 012 ls
    // | | ls NOK
    while (sh->line[i])
    {
        ft_init_cmd_aux_0(sh, &i, &squote, &dquote);
        len = (i - start);
        if (len)
        {
            ft_init_cmd_aux_1(sh, ft_substr(sh->line, start, len));
            if (sh->ret < 0)
                return ;
        }
        if (sh->line[i] == '|')
        {
            ft_init_cmd_aux_1(sh, ft_strdup("|"));
            if (sh->ret < 0)
                return ;
            start = ++i;
        }
        ft_print_list(sh);
    }
    printf("Dentro da init cmd -> Fim\n");
}
*/


/*
        while (sh->line[i])
        {
            while (sh->line[i] && (!((sh->line[i] == '|') && !(squote % 2) && !(dquote % 2))))
            {
                if (sh->line[i] == '\'')
                    squote++;
                else if (sh->line[i] == '\"')
                    dquote++;
                else if (sh->line[i] == '|' && !(squote % 2) && !(dquote % 2))
                    break ;
                i++;
            }
        }
*/