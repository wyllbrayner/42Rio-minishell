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

void ft_valid_empty_cmd(t_minishell *sh);
void ft_valid_amount_of_quotes(t_minishell *sh);
void ft_put_cmd_in_lst(t_minishell *sh);
void ft_valid_lexcal_cmd(t_minishell *sh);
void ft_redirect(t_minishell *sh);
void ft_heredoc(t_minishell *sh);

void ft_parse(t_minishell *sh)
{
//    printf("Dentro da parse | inicio errnbr: %i\n", sh->errnbr);
    if (sh)
    {
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
//    printf("Dentro da parse | intermediario errnbr: %i\n", sh->errnbr);
        add_history(sh->line);
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_amount_of_quotes(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect_0(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect_1(sh);
        if (sh->ret < 0)
            return ;
        ft_cmd_builder(sh);
        if (sh->ret < 0)
            return ;
        ft_print_list(sh->head);
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            sh->errnbr = errno;
            return ;
        }
//        ft_print_list(sh->head);
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
        {
            sh->errnbr = 258;
            return ;
        }
//        printf("Após a lexcal_cmd ret: %d\n", sh->ret);
//        ft_print_rev_list(sh->head);
/*
        ft_interpreter(sh);
        if (sh->ret < 0)
            return ;
*/
        ft_redirect(sh);
        if (sh->ret < 0)
            return ;
        ft_heredoc(sh);
        if (sh->ret < 0)
            return ;

//        printf("Após a valid quotes ret: %d\n", sh->ret);
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim errnbr: %i\n", sh->errnbr);
}

void ft_valid_empty_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_empty_cmd | inicio errnbr: %i\n", sh->errnbr);
    sh->tmp0 = ft_strtrim(sh->line, " ");
    if (!sh->tmp0)
    {
        sh->errnbr = errno;
        sh->ret = -3;
        return ;
    }
    if ((ft_strlen(sh->tmp0) == 0))
    {
        sh->ret = -8;
    }
//    printf("Dentro da ft_valid_empty_cmd | intermediário errnbr: %i\n", sh->errnbr);
    ft_free_minishell_single_aux(sh->line);
    sh->line = NULL;
    sh->line = sh->tmp0;
    sh->tmp0 = NULL;
//    ft_free_minishell_single_aux(sh->tmp1);
//    sh->tmp1 = NULL;
//    printf("Dentro da ft_valid_empty_cmd | fim errnbr: %i\n", sh->errnbr);
}

void ft_valid_amount_of_quotes(t_minishell *sh)
{
    long    i;
    long    squote;
    long    dquote;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    i = 0;
    squote = 0;
    dquote = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == '\'')
            squote++;
        else if (sh->line[i] == '\"')
            dquote++;
        i++;
    }
    if (!ft_valid_quote(squote, dquote))
        sh->ret = -5;
//    printf("Dentro da ft_valid_quotes | fim\n");
}

void    ft_valid_redirect_1(t_minishell *sh)
{
//    printf("Dentro da valid_redirect_1 -> Início\n");
    long var[5];

//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
    ft_cmd_builder_init_var(sh->caract, "><", var);
    while (sh->line[var[0]])
    {
//        printf("Dentro da valid_redirect_1 -> loop\n");
        ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
        if (sh->line[var[0]])
            var[0]++;
        else
            break ;
        while (sh->line[var[0]])
        {
            if (ft_isspace(sh->line[var[0]]))
                var[0]++;
            else
                break ;
        }
        if (sh->line[var[0]] == '|')
        {
            sh->ret = -6;
            sh->erro = "|";
            sh->errnbr = 258;
            break ;
        }
        if (sh->line[var[0]])
            var[0]++;
    }
//    printf("Dentro da valid_redirect_1 -> Fim\n");
}

void    ft_valid_redirect_0(t_minishell *sh)
{
//    printf("Dentro da valid_redirect 0 -> Início\n");
    long var[5];

//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
    ft_cmd_builder_init_var(sh->caract, "><", var);
    while (sh->line[var[0]])
    {
//        printf("Dentro da valid_redirect 0 -> loop\n");
        ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
//        printf("Dentro da valid_redirect 0 -> loop após aux_0 var[0]: %ld\n", var[0]);
        if (ft_strchr("<>", sh->line[var[0]]) && (ft_strlen(sh->line) - var[0]) >= 3)
        {
            if (var[0] == 0)
            {
                if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
                {
//                    printf("Dentro da valid_redirect 0 -> 1° if\n");
                    sh->ret = -6;
                    sh->erro = ">>>";
                    sh->errnbr = 258;
                    return ;
                }
                else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
                {
//                    printf("Dentro da valid_redirect 0 -> 2° if\n");
                    sh->ret = -6;
                    sh->erro = "<<<";
                    sh->errnbr = 258;
                    return ;
                }
            }
            else
            {
                if (!ft_strchr("_-", sh->line[(var[0] - 1)]))
                {
                    if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
                    {
//                        printf("Dentro da valid_redirect 0 -> 1° if\n");
                        sh->ret = -6;
                        sh->erro = ">>>";
                        sh->errnbr = 258;
                        return ;
                    }
                    else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
                    {
//                        printf("Dentro da valid_redirect 0 -> 2° if\n");
                        sh->ret = -6;
                        sh->erro = "<<<";
                        sh->errnbr = 258;
                        return ;
                    }   
                }
            }
            var[0]++;
        }
        else
            break ;
    }
//    printf("Dentro da valid_redirect 0 -> Fim\n");
}

void ft_valid_lexcal_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_lexcal_cmd -> Início - errnbr: %i\n", sh->errnbr);
    t_node  *tmp;
    int     tmp_ret;

    tmp = sh->head;
    sh->ret = -6;
    sh->erro = "|";
    tmp_ret = 0;
    if (sh->errnbr != 0)
        tmp_ret = sh->errnbr;
    sh->errnbr = 258; ///// confirmar que o código de retorno no Mac é este para TODOS os cenarios.
    while (tmp)
    {
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
            return ;
        if ((!tmp->next) && (tmp->cmd[0][0] == '|'))
            return ;
        if ((!tmp->next) && (tmp->cmd[0][0] == '>'))
        {
            sh->erro = NULL;
            return ;
        }
        if ((tmp->cmd[0][0] == '|') && (tmp->next))
        {
            if (!tmp->next->cmd[0])
                return ;
            if (tmp->next->cmd[0][0] == '|')
                return ;
        }
        if ((tmp->cmd[0][0] == '>') && (tmp->next))
        {
            if (!tmp->next->cmd[0])
                return ;
            if (tmp->next->cmd[0][0] == '>')
            {
                sh->erro = ">";
                return ;
            }
        }
        tmp = tmp->next;
    }
    sh->ret = 0;
    sh->erro = NULL;
    sh->errnbr = tmp_ret;
//    printf("Dentro da ft_valid_lexcal_cmd -> Fim - errnbr: %i\n", sh->errnbr);
}

void    ft_heredoc(t_minishell *sh)
{
//    printf("Dentro da ft_heredoc -> Início\n");
    t_node *head;

    head = sh->head;
    while (head && (sh->ret == 0))
    {
//        printf("nó [token    ]: %s\n", head->token);
//        printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//        printf("nó [first cmd]: %s\n", head->first_cmd);
        if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && head->first_cmd[0] != '>')
        {
            if (head->prev)
            {
                if (ft_strncmp(head->prev->first_cmd, "<<", 2) == 0)
                {
                    ft_heredoc_builder(sh, head);
                    if (sh->ret < 0)
                        break ;
                }
            }
        }
        head = head->next;
    }
//    printf("Dentro da ft_heredoc -> Fim\n");
}

void    ft_redirect_aux_1(t_minishell *sh, t_node *node, int type)
{
    int j;
//    printf("Dentro da ft_redirect_aux_1 -> Início type: %d\n", type);
    j = 0;
    while (node->redirect_file[j])
    {
//        printf("Dentro da ft_redirect_aux_1 | dentro do loop type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
        if (j > 0)
        {
//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | dentro do 1ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
            sh->ret = -7;
            sh->erro = node->redirect_file[j];
            sh->errnbr = 1;
            return ;
        }
//        printf("Dentro da ft_redirect_aux_1 -> Início type: %d | j: %d | node->redirect_file[%d]: %s pré open\n", type, j, j, node->redirect_file[j]);
        if (type == 1)
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else if (type == 2)
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
        else if (type == 3)
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_RDONLY);
        if (node->redirect_file_fd[j] == -1)
        {
//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | dentro do 2ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
            sh->ret = -7;
            sh->erro = node->redirect_file[j];
            sh->errnbr = 1;
            return ;
        }
        j++;
//        printf("Dentro da ft_redirect_aux_1 -> Início type: %d | j: %d | node->redirect_file[%d]: %s pós open\n", type, j, j, node->redirect_file[j]);
    }
//    printf("Dentro da ft_redirect_aux_1 -> Fim\n");
}

void    ft_redirect_aux_0(t_minishell *sh, t_node *node)
{
//    printf("Dentro da ft_redirect_aux_0 -> Início\n");
    node->redirect_file = ft_split(node->token, ' ');
    if (!node->redirect_file)
    {
        sh->ret = -3;
        sh->errnbr = errno;
        return;
    }
/*
    int j = 0;
    while (node->redirect_file[j])
    {
//        printf("após split: node->redirect_file[%i]: %s\n", j, node->redirect_file[j]);
        j++;
    }
*/
//    printf("após split: node->redirect_file[%i]: %s\n", j, node->redirect_file[j]);

    while (node->redirect_file[node->redirect_file_fd_amount])
    {
//        printf("split para o arquivo: %s\n", node->redirect_file[node->redirect_file_fd_amount]);
        node->redirect_file_fd_amount++;
    }
    node->redirect_file_fd = (int *)malloc(sizeof(int) * node->redirect_file_fd_amount);
    if (!node->redirect_file_fd)
    {
        sh->ret = -3;
        sh->errnbr = errno;
        return;
    }
//    printf("Conseguiu mallocar %i fds\n", node->redirect_file_fd_amount);
//    printf("para node->token: %s o prev é: %s\n", node->token, node->prev->token);
    if (node->prev) // quando for colocar na norma, considerar retirar este if, pois a função anterior já valida o nó anterior. Logo, garante que o nó anterior exite. Assim, não se faz necessário revalidar aqui. 
    {
        if (ft_strncmp(node->prev->token, ">", 2) == 0)
        {
//            printf("Arquivo de saida normal\n");
            ft_redirect_aux_1(sh, node, 1);
        }
        else if (ft_strncmp(node->prev->token, ">>", 3) == 0)
        {
//            printf("Arquivo de saida com append\n");
            ft_redirect_aux_1(sh, node, 2);
        }
        else if (ft_strncmp(node->prev->token, "<", 2) == 0)
        {
//            printf("Arquivo de entrada normal\n");
            ft_redirect_aux_1(sh, node, 3);
        }
    }
//    printf("Dentro da ft_redirect_aux_0 -> Fim\n");
}

void    ft_redirect(t_minishell *sh)
{
//    printf("Dentro da ft_redirect -> Início\n");
    t_node *head;

    head = sh->head;
    while (head && (sh->ret == 0))
    {
//        printf("nó [token    ]: %s\n", head->token);
//        printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//        printf("nó [first cmd]: %s\n", head->first_cmd);
        if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && head->first_cmd[0] != '>')
        {
            if (head->prev)
            {
                if ((ft_strncmp(head->prev->first_cmd, "<", 2) == 0) || (ft_strncmp(head->prev->first_cmd, ">", 2) == 0) || (ft_strncmp(head->prev->first_cmd, ">>", 3) == 0))
                {
//                    printf("Charmar a builder_redirect head->token: %s\n", head->token);
                    ft_redirect_aux_0(sh, head);
                    if (sh->ret < 0)
                        break ;
                }
            }
        }
        head = head->next;
    }
//    printf("Dentro da ft_redirect -> Fim\n");
}



/*
void    ft_valid_redirect(t_minishell *sh)
{
    printf("Dentro da valid_redirect -> Início\n");
    long var[5];

//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
    ft_cmd_builder_init_var(sh->caract, "><", var);
    while (sh->line[var[0]])
    {
        printf("Dentro da valid_redirect -> loop\n");
        ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
        printf("Dentro da valid_redirect -> loop após aux_0 var[0]: %ld\n", var[0]);
        if (ft_strchr("<>", sh->line[var[0]]) && (ft_strlen(sh->line) - var[0]) >= 3)
        {
            if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
            {
                printf("Dentro da valid_redirect -> 1° if\n");
                sh->ret = -6;
                sh->erro = ">>>";
                return ;
            }
            else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
            {
                printf("Dentro da valid_redirect -> 2° if\n");
                sh->ret = -6;
                sh->erro = "<<<";
                return ;
            }
            var[0]++;
        }
        else
            break ;
    }
    printf("Dentro da valid_redirect -> Fim\n");
}
*/