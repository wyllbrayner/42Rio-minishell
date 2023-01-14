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

void ft_free_minishell(t_minishell *sh, int status)
{
    long i;

    i = 0;
    if (status == 0)
    {
        free(sh->line);
        sh->line = NULL;
    }
    if (status == 1)
    {
        while (i < sh->parse_len)
        {
            free(sh->parse_str[i]);
            sh->parse_str[i++] = NULL;
        }
        free(sh->parse_str);
        sh->parse_str = NULL;
    }
}

void ft_parse(t_minishell *sh) // sei que será necessário separar a string recebida para análise futura.
{
    long    i; // criei um contador para também retornar a quantidade de parametros recebida.

    sh->parse_str = ft_split(sh->line, ' ');
    sh->parse_len = -1;
    if (*sh->parse_str != NULL)
    {
        i = 0;
        while (sh->parse_str[i])
            i++;
        sh->parse_len = i;
    }
}

void ft_minishell(void)
{
    t_minishell sh;
    int         count;  // só para simular uma forma de saída temporária

    sh.running = TRUE;
    sh.line = NULL;
    count = 0;  // só para simular uma forma de saída temporária
    while (sh.running)
    {
        sh.line = readline("minishell: ");
        if (!sh.line)
        {
            printf("readline retornou nulo e o programa será encerrado!\n");
            sh.running = FALSE;
        }
        else
        {
            printf("radline retornou um ponteiro contendo %s\n", sh.line);
//            add_history(sh.line);
            ft_parse(&sh);
            if (sh.parse_len == -1)
            {
                printf("split retornou error e o programa será encerrado agora!\n");
                sh.running = FALSE;
            }
            else
            { //testando o retorno da split. Podemos usar essa parte para dar sequencia no programa.
                long i = 0;
                while(i < sh.parse_len)
                {
                    printf("comando %li recebido da split: %s\n", i, sh.parse_str[i]);
                    i++;
                }
                ft_free_minishell(&sh, 1);
            }
            ft_free_minishell(&sh, 0);
        }
        count++;  // só para simular uma forma de saída temporária
        if (count == 3) // só para simular uma forma de saída temporária
            sh.running = FALSE;
    }
    exit(EXIT_SUCCESS); //mesmo com isto está dando still reachable: 208,329 bytes in 231 blocks no valgrind.
}

int main(void)
{
    ft_minishell();
    return (0);
}