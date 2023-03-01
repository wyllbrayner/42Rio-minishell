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

void ft_expander_dquote(t_minishell *sh, t_node *node)
{
    long i;
    long j;

    i = 0;
    j = 0;
    sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1)); // malloque tmp1 com a quantidade de caracteres de token + 1 para o nullo.
    if (!sh->tmp1)
        sh->ret = -3;
    else // se conseguiu mallocar, faça
    {
        while (node->token[i]) // percorra todos os caracteres de token.
        {
            if (node->token[i] != '\"') //se o caracter de token for diferente de '\"', faça
                sh->tmp1[j++] = node->token[i]; // copie o caracter de token para tmp1 
            i++; // adicione um ao contador
        }
        sh->tmp1[j] = '\0'; // feche a string tmp1 com nullo
        ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
    }
}

void ft_expander_squote(t_minishell *sh, t_node *node)
{
    long i;
    long j;
    long squote;

    i = 0;
    j = 0;
    squote = 0;
    sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1));
    if (!sh->tmp1)
        sh->ret = -3;
    else
    {
        while (node->token[i]) // percorra todos os caracteres de token
        {
            while (node->token[i]) // percorra token, enquanto token existir e for igual a '\'', faça
            {
                if (node->token[i] == '\'')
                {
                    i++; // adicione um ao contador
                    squote++; // adicione um ao contador de aspas simples
                }
                else
                    break ;
            }
/*
            while (node->token[i] && node->token[i] == '\'') // percorra token, enquanto token existir e for igual a '\'', faça
            {
                i++; // adicione um ao contador
                squote++; // adicione um ao contador de aspas simples
            }
*/
            if (squote % 2) // verifique se a quantidade de aspas simples é impar
                sh->tmp1[j++] = '\''; // se for impar, acrescente uma aspas simples em tmp1
            squote = 0; // reinicie o contador de aspas simples
            while (node->token[i]) // percorra token e faça
            {
                if (node->token[i] != '\'') // se token for diferente de '\'', faça
                    sh->tmp1[j++] = node->token[i]; // copie token para tmp1
                else // caso contrário
                    break ; // interrompa
                i++; // adicione um ao contador
            }
        }
        sh->tmp1[j] = '\0'; // feche a string tmp1 com nullo
        ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
    }
}

void ft_expander_quote(t_minishell *sh, t_node *node)
{
//    printf("Dentro da ft_expander_quote - Início\n");
//    printf("Antes de ft_expand_variable_dquote, node->token: %s\n", node->token);
    ft_expander_dquote(sh, node);
    if (sh->ret < 0)
        return ;
//    printf("Após     ft_expand_variable_dquote, node->token: %s\n", node->token);
//    printf("===================================================\n");
//    printf("Antes de ft_expand_variable_squote, node->token: %s\n", node->token);
    ft_expander_squote(sh, node);
    if (sh->ret < 0)
        return ;
//    printf("Após     ft_expand_variable_squote, node->token: %s\n", node->token);
//    printf("Dentro da ft_expander_quote - Fim\n");
}

void    ft_expand_variable_0(t_minishell *sh, t_node *node, long *var)
{
/*
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
    printf("Dentro da ft_expand_variable_0 - Início\n");
*/
    if (!sh->tmp5)
    {
        sh->tmp0 = ft_substr(node->token, var[0], var[5]);
//        printf("Dentro do if   tmp0: %s#\n", sh->tmp0);
        if (!sh->tmp0)
        {
            sh->ret = -3;
            return ;
        }
    }
    else
    {
        if (node->token[var[0]] != '$')
        {
            sh->tmp0  = ft_substr(node->token, var[0], (var[5] - var[0]));
            if (!sh->tmp0)
            {
                ft_free_minishell_single_aux(sh->tmp5);
                sh->tmp5 = NULL;
                sh->ret = -3;
                return ;
            }
//            printf("Dentro do else   tmp0: %s#\n", sh->tmp0);
            sh->tmp1 = ft_strjoin(sh->tmp5, sh->tmp0);
//            printf("Dentro do else, join de tmp5: %s# e tmp0: %s# em tmp1: %s#\n", sh->tmp5, sh->tmp0, sh->tmp1);
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
            ft_free_minishell_single_aux(sh->tmp5);
            sh->tmp5 = NULL;
            if (!sh->tmp1)
            {
                sh->ret = -3;
                return ;
            }
            sh->tmp0 = sh->tmp1;
            sh->tmp1 = NULL;
        }
        else
        {
            sh->tmp0 = sh->tmp5;
            sh->tmp5 = NULL;
            var[5] = var[0];
        }
//        printf("Dentro do else, troca os ponteiros de tmp0: %s# e tmp1: %s#\n", sh->tmp0, sh->tmp1);
    }
/*
    printf("Após os ifs\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/
    if (node->token[var[5]])
    {
        if (node->token[var[5]] != '~')
            var[5]++;
    }
    var[0] = var[5];
//    printf("Após colocar o histórico tmp0 v[0] recebe v[5] -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    while (node->token[var[5]] && !(ft_strchr("/$~\'", node->token[var[5]])) && !ft_isspace(node->token[var[5]]))
        var[5]++;
//    printf("Andou até o próximo '$~/\' (espaço)'        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    if ((var[0] == var[5]) && (node->token[var[5]] == '~') && (node->token[(var[5] - 1)] == ' '))
    {
        if (!node->token[(var[5] + 1)])
        {
//            printf("é ~\n");
            sh->tmp5 = ft_strdup("HOME");
        }
        else if (((node->token[(var[5] + 1)] == ' ') || (node->token[(var[5] + 1)] == '/')))
        {
//            printf("é ~\n");
            sh->tmp5 = ft_strdup("HOME");
        }
    }
    else
        sh->tmp5 = ft_substr(node->token, var[0], (var[5] - var[0]));
//    printf("malloca len: %ld posições a partir de: var[0]: %ld até var[5]: %ld -> tmp5: %s\n", (var[5] - var[0]), var[0], var[5], sh->tmp5);
    if (!sh->tmp5)
    {
//        printf("sh->tmp5 não conseguiu mallocar\n");
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    sh->tmp1 = ft_strjoin(sh->tmp5, "=");
//    printf("join de tmp5: %s com = em tmp1: %s\n", sh->tmp5, sh->tmp1);
    ft_free_minishell_single_aux(sh->tmp5);
    sh->tmp5 = NULL;
    if (!sh->tmp1)
    {
//        printf("sh->tmp1 não conseguiu mallocar\n");
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    var[1] = ft_strlen(sh->tmp1);
    var[0] = 0;
    var[3] = FALSE;
//    printf("Antes de ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
//    printf("Após     ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    if (var[3])
    {
        var[4] = ft_strchr_i(sh->env[var[2]], '=');
        sh->tmp5 = ft_substr(sh->env[var[2]], (var[4] + 1), ft_strlen(sh->env[var[2]]) - var[4]);
//        printf("ft_unset_aux_1 retornou true e tmp2: %s\n", sh->tmp2);
    }
    else
    {
        if (ft_strncmp(sh->tmp1, "?=", 3) == 0)
        {
            sh->tmp5 = ft_itoa(sh->errno);
//            printf("ft_unset_aux_1 retornou false, mas tmp1 = $?=: %s\n", sh->tmp2);
        }
        else
        {
            sh->tmp5 = ft_strdup("");
//            printf("ft_unset_aux_1 retornou false, malloca espaço: #%s#\n", sh->tmp2);
        }
    }
    ft_free_minishell_single_aux(sh->tmp1);
    sh->tmp1 = NULL;
    if (!sh->tmp5)
    {
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    sh->tmp1 = ft_strjoin(sh->tmp0, sh->tmp5);
    ft_free_minishell_single_aux(sh->tmp0);
    sh->tmp0 = NULL;
    ft_free_minishell_single_aux(sh->tmp5);
    sh->tmp5 = NULL;
    if (!sh->tmp1)
        sh->ret = -3;
    sh->tmp5 = sh->tmp1;
    sh->tmp1 = NULL;
/*
    printf("Dentro da ft_expand_variable_0 - Fim\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/
}

void    ft_expand_variable(t_minishell *sh, t_node *node)
{
//    printf("Dentro da ft_expand_variable - Início (token: %s)\n", node->token);
    long    var[7] = {0};

    var[0] = 0;
    var[5] = 0;
    var[6] = FALSE;
    while (node->token[var[5]] && !ft_isspace(node->token[var[5]]))
        var[5]++;
    while (node->token[var[5]] && ft_isspace(node->token[var[5]]))
        var[5]++;
    while (node->token[var[5]])
    {
        while (node->token[var[5]] && !(ft_strchr("$~", node->token[var[5]])))
        {
            if (node->token[var[5]] == '\'')
            {
                if (var[6])
                {
                    var[6] = FALSE;
                }
                else
                    var[6] = TRUE;
            }
            var[5]++;
        }
        if (node->token[var[5]] && var[6])
        {
            while (node->token[var[5]] && node->token[var[5]] != '\'')
                var[5]++;
            var[6] = FALSE;
        }
        else
        {   
//            printf("Chama    a expand_variable_0 - v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
            ft_expand_variable_0(sh, node, var);
//            printf("Retorna da expand_variable_0 - v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
            if (sh->ret < 0)
                return ;
            var[0] = var[5];
            if (node->token[var[5]] == '\'')
            {
                if (var[6])
                {
                    var[6] = FALSE;
                }
                else
                    var[6] = TRUE;
            }
        }
        if (node->token[var[5]])
        {
            if (node->token[var[5]] != '~')
                var[5]++;
            else
            {
                var[5]++;
                var[0] = var[5];
            }
        }
    }
//    printf("Dentro da ft_expand_variable - Fim (token: %s)\n", node->token);
}

void    ft_expand_variable_cd(t_minishell *sh, t_node *node)
{
    long i;

    i = 0;
    while (node->cmd[i])
        i++;
    if (i == 1)
    {
        sh->tmp1 = ft_strdup("cd $HOME");
    	if (!sh->tmp1)
	    {
    		sh->ret = -3;
	    	return ;
    	}
        ft_builtin_cd_aux_2(sh, node);
        if (sh->ret < 0)
            return ;
    }
}

void ft_expander_variable(t_minishell *sh, t_node *node)
{
//    printf("Dentro da ft_expander_variable - Início\n");
//    printf("token: #%s# e first_cmd: #%s#\n", node->token, node->first_cmd);
    sh->ret = 0;
    if (ft_strncmp(node->first_cmd, "cd", 2) == 0)
    {
//        printf("Estender variável para cd: %s#\n", node->token);
        ft_expand_variable_cd(sh, node);
    }
//        printf("Estender variável para diferente de cd\n");
//    printf("Antes de 1° ft_expand_variable, node->token: %s\n", node->token);
    ft_expand_variable(sh, node);
//        printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
    if (sh->tmp5)
    {
        sh->tmp1 = sh->tmp5;
        sh->tmp5 = NULL;
        ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
    }
//    printf("Após  da 1º ft_expand_variable, node->token: %s\n", node->token);
//    printf("Dentro da ft_expander_variable - Fim\n");
}

void    ft_interpreter(t_minishell *sh)
{
//    printf("Dentro da ft_interpreter - Início\n");
    t_node *head;

    head = sh->head;
    while (head && (sh->ret == 0)) // percorre todos os nós
    {
        if (head->token[0] != '|') // se o nó não começar com pipe, faça.
        {
            ft_expander_quote(sh, head);
            ft_expander_variable(sh, head);
        }
//        else
//            printf("Pula o '|' \n");
        head = head->next;
    }
//    printf("Dentro da ft_interpreter - Fim\n");
}

/*
//  export      TEST='$HOME'$PATH $PROJ 
    long    start;  // var[0];
    long    end;    // var[1];
    long    i_env;  // var[2];
    long    status; // var[3];
    long    len;        // var[4];
    long    j;          // var[5];
    long    quote;      // var[6];
//  echo      TEST='$HOME'$PATH$PROJ 
//  echo      TEST='$HOME'$PROJ $PATH 
//  echo      TEST=$?$HOME'$PROJ' $PATH
//  echo      TEST='$HOME'$PATH' ' $USER
//  echo      TEST=$?$HOME'$PROJ' '$PATH'''
//  echo    $HOME~ TEST='$HOME'  $PATH' ' ~ $USER // loop infinito
//  ls $HOME~ ~/projetos   
// ls "$HOME" | exit | echo "sair daqui | agora"
// echo "'''''$HOME'''''" | e''xi''t | echo "'''sair daqui | agora'''" | ls "''''$HOME''''"/PROJETOS
// tmp0 = null
// tmp1 = null
// tmp2 = null
// tmp5 = ls /home/wyllbrayner /projetosNULL
//                    [0]
//                    [5]
//  00000000001111111111222222
//  01234567890123456789012345
//  ls $HOME~ /projetos 
*/



/*
void ft_expander_variable(t_minishell *sh, t_node *node)
{
    printf("Dentro da ft_expander_variable - Início\n");
    printf("token: #%s# e first_cmd: #%s#\n", node->token, node->first_cmd);
    sh->ret = 0;
    if (ft_strncmp(node->first_cmd, "cd", 2) != 0)
    {
//        printf("Estender variável para diferente de cd\n");
        printf("Antes de 1° ft_expand_variable, node->token: %s\n", node->token);
        ft_expand_variable(sh, node);
//        printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
        if (sh->tmp5)
        {
            sh->tmp1 = sh->tmp5;
            sh->tmp5 = NULL;
            ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
        }
        printf("Após  da 1º ft_expand_variable, node->token: %s\n", node->token);
    }
    else
    {
        printf("Estender variável para cd: %s#\n", node->token);
        ft_expand_variable_cd(sh, node);
        printf("Antes de 1° ft_expand_variable, node->token: %s\n", node->token);
        ft_expand_variable(sh, node);
//        printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
        if (sh->tmp5)
        {
            sh->tmp1 = sh->tmp5;
            sh->tmp5 = NULL;
            ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
        }
        printf("Após  da 1º ft_expand_variable, node->token: %s\n", node->token);
    }
    printf("Dentro da ft_expander_variable - Fim\n");
}
*/

/*
void    ft_expand_variable_0(t_minishell *sh, t_node *node, long *var)
{
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
    printf("Dentro da ft_expand_variable_0 - Início\n");
    if (!sh->tmp5)
    {
        sh->tmp0 = ft_substr(node->token, var[0], var[5]);
        printf("Dentro do if   tmp0: %s#\n", sh->tmp0);
        if (!sh->tmp0)
        {
            sh->ret = -3;
            return ;
        }
    }
    else
    {
        if (node->token[var[0]] != '$')
        {
            sh->tmp0  = ft_substr(node->token, var[0], (var[5] - var[0]));
            if (!sh->tmp0)
            {
                ft_free_minishell_single_aux(sh->tmp5);
                sh->tmp5 = NULL;
                sh->ret = -3;
                return ;
            }
            printf("Dentro do else   tmp0: %s#\n", sh->tmp0);
            sh->tmp1 = ft_strjoin(sh->tmp5, sh->tmp0);
            printf("Dentro do else, join de tmp5: %s# e tmp0: %s# em tmp1: %s#\n", sh->tmp5, sh->tmp0, sh->tmp1);
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
            ft_free_minishell_single_aux(sh->tmp5);
            sh->tmp5 = NULL;
            if (!sh->tmp1)
            {
                sh->ret = -3;
                return ;
            }
            sh->tmp0 = sh->tmp1;
            sh->tmp1 = NULL;
        }
        else
        {
            sh->tmp0 = sh->tmp5;
            sh->tmp5 = NULL;
            var[5] = var[0];
        }
        printf("Dentro do else, troca os ponteiros de tmp0: %s# e tmp1: %s#\n", sh->tmp0, sh->tmp1);
    }
    printf("Após os ifs\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
    if (node->token[var[5]])
    {
        if (node->token[var[5]] != '~')
            var[5]++;
    }
    var[0] = var[5];
    printf("Após colocar o histórico tmp0 v[0] recebe v[5] -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    while (node->token[var[5]] && !(ft_strchr("/$~\'", node->token[var[5]])) && !ft_isspace(node->token[var[5]]))
        var[5]++;
    printf("Andou até o próximo '$~/\' (espaço)'        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    if ((var[0] == var[5]) && (node->token[var[5]] == '~') && (node->token[(var[5] - 1)] == ' '))
    {
        if (!node->token[(var[5] + 1)])
        {
            printf("é ~\n");
            sh->tmp2 = ft_strdup("HOME");   // será que podemos alocar em tmp5?????????????????
        }
        else if (((node->token[(var[5] + 1)] == ' ') || (node->token[(var[5] + 1)] == '/')))
        {
            printf("é ~\n");
            sh->tmp2 = ft_strdup("HOME");   // será que podemos alocar em tmp5?????????????????
        }
    }
    else
        sh->tmp2 = ft_substr(node->token, var[0], (var[5] - var[0]));   // será que podemos alocar em tmp5?????????????????
    printf("malloca len: %ld posições a partir de: var[0]: %ld até var[5]: %ld -> tmp2: %s\n", (var[5] - var[0]), var[0], var[5], sh->tmp2);
    if (!sh->tmp2)
    {
        printf("sh->tmp2 não conseguiu mallocar\n");
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    sh->tmp1 = ft_strjoin(sh->tmp2, "=");
    printf("join de tmp2: %s com = em tmp1: %s\n", sh->tmp2, sh->tmp1);
    ft_free_minishell_single_aux(sh->tmp2);
    sh->tmp2 = NULL;
    if (!sh->tmp1)
    {
        printf("sh->tmp1 não conseguiu mallocar\n");
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    var[1] = ft_strlen(sh->tmp1);
    var[0] = 0;
    var[3] = FALSE;
    printf("Antes de ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
    printf("Após     ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
    if (var[3])
    {
        var[4] = ft_strchr_i(sh->env[var[2]], '=');
        sh->tmp2 = ft_substr(sh->env[var[2]], (var[4] + 1), ft_strlen(sh->env[var[2]]) - var[4]);    // será que podemos alocar em tmp5?????????????????
        printf("ft_unset_aux_1 retornou true e tmp2: %s\n", sh->tmp2);
    }
    else
    {
        if (ft_strncmp(sh->tmp1, "?=", 3) == 0)
        {
            sh->tmp2 = ft_itoa(sh->errno);    // será que podemos alocar em tmp5?????????????????
            printf("ft_unset_aux_1 retornou false, mas tmp1 = $?=: %s\n", sh->tmp2);
        }
        else
        {
            sh->tmp2 = ft_strdup("");   // será que podemos alocar em tmp5?????????????????
            printf("ft_unset_aux_1 retornou false, malloca espaço: #%s#\n", sh->tmp2);
        }
    }
    ft_free_minishell_single_aux(sh->tmp1);
    sh->tmp1 = NULL;
    if (!sh->tmp2)
    {
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->ret = -3;
        return ;
    }
    sh->tmp5 = ft_strjoin(sh->tmp0, sh->tmp2);   // realizando a alteração acima, realizar o join de tmp0 e tmp2 em tmp1, mas será necessário realocar o ponteiro de tmp1 para tmp5 e apontar tmp1 para null. deixando tmp2 sem utilização neste ciclo. 
    ft_free_minishell_single_aux(sh->tmp0);
    sh->tmp0 = NULL;
    ft_free_minishell_single_aux(sh->tmp2);
    sh->tmp2 = NULL;
    if (!sh->tmp5)
        sh->ret = -3;
    printf("Dentro da ft_expand_variable_0 - Fim\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
}
*/
