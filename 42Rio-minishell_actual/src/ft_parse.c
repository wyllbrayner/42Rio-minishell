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

void ft_valid_empty_cmd(t_minishell *sh)
{
//    printf("Dentro da ft_valid_empty_cmd | inicio\n");
    sh->tmp1 = ft_strtrim(sh->line, " ");
    if (!sh->tmp1)
    {
        sh->ret = -3;
        return ;
    }
    if ((ft_strlen(sh->tmp1) == 0))
    {
        sh->ret = -8;
    }
    ft_free_minishell_single_aux(sh->tmp1);
//    printf("Dentro da ft_valid_empty_cmd | fim\n");
}

void ft_valid_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    if (sh)
    {
        i = 0;
        count_s = 0;
        count_d = 0;
        while (sh->line[i])
        {
            if (sh->line[i] == '\'')
                count_s++;
            else if (sh->line[i] == '\"')
                count_d++;
            i++;
        }
        if (((count_s % 2) != 0) || ((count_d % 2) != 0))
        {
            sh->ret = -5;
        }
    }
//    printf("Dentro da ft_valid_quotes | fim\n");
}

int ft_valid_command_aux(t_minishell *sh, char *cmd)
{
//    printf("Dentro da ft_valid_comand_aux | inicio\n");
    if (sh && cmd)
    {
        if (ft_strncmp(cmd, "echo", 5) == 0)
            return (1);
        else if (ft_strncmp(cmd, "cd", 3) == 0)
            return (1);
        else if (ft_strncmp(cmd, "pwd", 4) == 0)
            return (1);
        else if (ft_strncmp(cmd, "export", 7) == 0)
            return (1);
        else if (ft_strncmp(cmd, "unset", 6) == 0)
            return (1);
        else if (ft_strncmp(cmd, "env", 4) == 0)
            return (1);
        else if (ft_strncmp(cmd, "exit", 5) == 0)
            return (1);
        else
        {
            sh->tmp1 = ft_access_command(cmd, sh->path);
            if (!sh->tmp1)
                return (0);
            ft_free_minishell_single_aux(sh->tmp1);
            return (1);
        }
    }
//    printf("Dentro da ft_valid_comand_aux | fim\n");
    return (0);
}

/*
int ft_pipe_or_redirect(t_minishell *sh, long i)
{
    return (sh->parse_str[i][0] == '|' || sh->parse_str[i][0] == '<' || sh->parse_str[i][0] == '>');
}
*/

int ft_pipe_or_redirect(char *cmd)
{
    return (cmd[0] == '|');
//    return (cmd[0] == '|' || cmd[0] == '<' || cmd[0] == '>');
}

int ft_valid_file(t_minishell *sh, long i)
{
    int fd;

    fd = open(sh->parse_str[i], O_WRONLY | O_CREAT, 0666);
    if (fd == -1)
        return (0);
    else
    {
        close(fd);
        return (1);
    }
}

//  0   1        2             3 4 5    6        7 8 9      10      11 
// ls -la Makefile src/ft_main.c | | grep Makefile > > test1.c test2.c

/*
void ft_valid_lexcal_cmd(t_minishell *sh)
{
    t_node  *tmp;

    tmp = sh->head;
    while (tmp)
    {
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro ="|"; 
            return ;
        }
        else if ((tmp->cmd[0][0] == '|') && (tmp->next) && (tmp->next->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro = "|";
            return ;
        }
        tmp = tmp->next;
        i++;
    }
}
*/

void ft_valid_lexcal_cmd(t_minishell *sh)
{
    t_node  *tmp;

    tmp = sh->head;
    while (tmp)
    {
//        printf("cmd[0] de tmp: %s\n", tmp->cmd[0]);
//        if (tmp->prev)
//        {
//            if (tmp->prev->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do prev\n");
//                sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->prev: %s\n", tmp->prev->cmd[0]);
//        }
//        if (tmp->next)
//        {
//            if (tmp->next->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do next\n");
//                sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->next: %s\n", tmp->next->cmd[0]);
//        }
//        sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//        sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro ="|"; 
            return ;
        }
        else if ((tmp->cmd[0][0] == '|') && (tmp->next) && (tmp->next->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro = "|";
            return ;
        }
//        else if ((tmp->cmd[0][0] == '|') && (sh->tmp3 && sh->tmp4))
//        {
//            if ((!ft_access_command(sh->tmp3[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp3[0];
//                return ;           
//            }
//            else if ((!ft_access_command(sh->tmp4[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp4[0];
//                return ;           
//            }
//        }
//        ft_free_minishell_double_aux(sh->tmp3);
//        ft_free_minishell_double_aux(sh->tmp4);
        tmp = tmp->next;
    }
}



//void ft_valid_lexcal_cmd(t_minishell *sh)
void ft_put_cmd_in_lst(t_minishell *sh)
{
    long    i;

//    printf("Dentro da valide_lexcal_cmd | inicio\n");
    i = 0;
    sh->tmp3 = (char **)malloc(sizeof(char *) * 2);
    if (!sh->tmp3)
    {
        sh->ret = -3;
        return ;
    }
    sh->tmp3[0] = NULL;
    sh->tmp3[1] = NULL;
    while (sh->parse_str[i])
    {
        sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
        i++;
//        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh, i))
        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp1 = ft_strjoin(sh->tmp3[0], " ");
            sh->tmp2 = ft_strjoin(sh->tmp1, sh->parse_str[i]);
            if (!sh->tmp1 || !sh->tmp2)
            {
                ft_free_minishell_single_aux(sh->tmp1);
                ft_free_minishell_single_aux(sh->tmp2);
                ft_free_minishell_double_aux(sh->tmp3);
                sh->ret = -3;
                return ;
            }
            ft_free_minishell_single_aux(sh->tmp3[0]);
            sh->tmp3[0] = sh->tmp2;
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp2 = NULL;
            i++;
        }
        ft_list_add_last(&sh->head, ft_node_create(sh->tmp3));
        sh->tmp3[0] = NULL;
//        if (sh->parse_str[i] && ft_pipe_or_redirect(sh, i))
        if (sh->parse_str[i] && ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
            ft_list_add_last(&sh->head, ft_node_create(sh->tmp3));
            sh->tmp3[0] = NULL;
        }
        if (sh->parse_str[i])
            i++;
    }
    ft_free_minishell_double_aux(sh->tmp3);
//    printf("Dentro da valide_lexcal_cmd | fim\n");
}

/*
void    ft_variable_expansion_aux(t_minishell *sh, t_node *no)
{
    long    var[4];
    long    len;
    long    caract;
    printf("Dentro da expansão de variáveis_aux - Início\n");
    var[0] = ft_strchr_i(no->cmd[0], '$');
    var[1] = ft_strlen(no->cmd[0]);
    sh->tmp1 = ft_substr(no->cmd[0], (var[0] + 1), (var[1] - var[0] - 1));
    sh->tmp2 = ft_strjoin(sh->tmp1, "=");
    printf("sh->tmp2: %s\n", sh->tmp2);
    ft_free_minishell_single_aux(sh->tmp1);
    sh->tmp1 = NULL;
    sh->tmp1 = sh->tmp2;
    sh->tmp2 = NULL;
    var[3] = FALSE;
    ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
    ft_free_minishell_single_aux(sh->tmp1);
    sh->tmp1 = NULL;
    if (var[3])
    {
        printf("var[3]: %ld | var[2](i): %ld | env: %s\n", var[3], var[2], sh->env[var[2]]);
        len = ((var[0] + (ft_strlen(sh->env[var[2]]) - ft_strchr_i(sh->env[var[2]], '='))));
        sh->tmp1 = (char *)malloc(sizeof(char) * len);
        if (!sh->tmp1)
        {
            printf("Não Mallocou\n");
            sh->ret = -3;
            return;
        }
        else
        {
            printf("Mallocou %ld posições\n", len);
//            sh->tmp1[--len] = '\0';
            ft_strlcpy(sh->tmp1, no->cmd[0], var[0]);
            printf("sh->tmp1 ( antes): %s\n", sh->tmp1);
            caract = ft_strchr_i(sh->env[var[2]], '=');
            printf("sh->env[%ld]: %s | caract: %ld\n", var[2], sh->env[var[2]], caract);
            ft_strlcpy(sh->tmp1+(var[0] - 1), sh->env[var[2]]+(caract + 1), ft_strlen(no->cmd[0]));
            printf("sh->tmp1 (depois): %s\n", sh->tmp1);
        }
    }
    else
        printf("Faça alguma coisa\n");
    printf("Dentro da expansão de variáveis_aux - Fim\n");
}
*/

void    ft_variable_expansion_aux(t_minishell *sh, t_node *no)
{
    long    var[4];
    long    len;
    long    caract;

    printf("Dentro da expansão de variáveis_aux - Início\n");
    var[0] = ft_strchr_i(no->cmd[0], '$');
    if (var[0])
    {
        var[1] = ft_strlen(no->cmd[0]);
        sh->tmp1 = ft_substr(no->cmd[0], (var[0] + 1), (var[1] - var[0] - 1));
        sh->tmp2 = ft_strjoin(sh->tmp1, "=");
        printf("sh->tmp2: %s\n", sh->tmp2);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        sh->tmp1 = sh->tmp2;
        sh->tmp2 = NULL;
        var[3] = FALSE;
        ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
        ft_free_minishell_single_aux(sh->tmp1);
        sh->tmp1 = NULL;
        if (var[3])
        {
            printf("var[3]: %ld | var[2](i): %ld | env: %s\n", var[3], var[2], sh->env[var[2]]);
            len = ((var[0] + (ft_strlen(sh->env[var[2]]) - ft_strchr_i(sh->env[var[2]], '='))));
            sh->tmp1 = (char *)malloc(sizeof(char) * len);
            if (!sh->tmp1)
            {
                printf("Não Mallocou\n");
                sh->ret = -3;
                return;
            }
            else
            {
                printf("Mallocou %ld posições\n", len);
                sh->tmp1[--len] = '\0';
                ft_strlcpy(sh->tmp1, no->cmd[0], (var[0] + 1));
                printf("sh->tmp1 ( antes): %s#\n", sh->tmp1);
                caract = ft_strchr_i(sh->env[var[2]], '=');
                printf("sh->env[%ld]: %s | caract: %ld\n", var[2], sh->env[var[2]], caract);
                ft_strlcpy(sh->tmp1+(var[0]), sh->env[var[2]]+(caract + 1), ft_strlen(sh->env[var[2]]) - caract);
                printf("sh->tmp1 (depois): %s\n", sh->tmp1);
            }
        }
        else
            printf("Faça alguma coisa\n");
        printf("Dentro da expansão de variáveis_aux - Fim\n");
    }
}

void ft_variable_expansion(t_minishell *sh)
{
    t_node *tmp;
    printf("Dentro da expansão de variáveis - Início\n");
    tmp = sh->head;
    while (tmp)
    {
        if (ft_strchr_i(tmp->cmd[0], '$') != 0)
        {
            printf("Nó: %s     possui %c\n", tmp->cmd[0], '$');
            ft_variable_expansion_aux(sh, tmp);
        }
        else
        {
            printf("Nó: %s não possui %c\n", tmp->cmd[0], '$');
        }

        tmp = tmp->next;
    }
    printf("Dentro da expansão de variáveis - Fim\n");
}

void ft_parse(t_minishell *sh)
{
//    printf("Dentro da parse | inicio\n");
    if (sh)
    {
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_quotes(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a valid quotes ret: %d\n", sh->ret);
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            return ;
        }
//        printf("Após a split ret: %d\n", sh->ret);
//        ft_valid_lexcal_cmd(sh);
        ft_put_cmd_in_lst(sh);
        if (sh->ret < 0)
            return ;
        ft_print_list(sh);
        ft_print_rev_list(sh);
//        printf("Após a lexcal_cmd ret: %d\n", sh->ret);
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
            return ;
        ft_variable_expansion(sh);
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim\n");
}


/*
        if (!ft_valid_command_aux(sh, sh->parse_str[i]) || !ft_valid_file(sh, i))
        {
            sh->ret = -4;
            sh->erro = sh->parse_str[i];
            ft_free_minishell_double_aux(sh->tmp3);
            return ;
        }
*/