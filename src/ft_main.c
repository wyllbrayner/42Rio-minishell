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

void ft_free_minishell_aux(char *str)
{
    if (str)
        free(str);
    str = NULL;
}

void ft_free_minishell(t_minishell *sh, int status)
{
    long i;

    i = 0;
    if (status == 0)
        ft_free_minishell_aux(sh->line);
    if (status == 1)
    {
        while (i < sh->parse_len)
        {
            ft_free_minishell_aux(sh->parse_str[i]);
            i++;
        }
        free(sh->parse_str);
        sh->parse_str = NULL;
    }
    if (status == 2)
    {
        ft_free_minishell_aux(sh->path);
        ft_free_minishell_aux(sh->pwd);
    }
}

void ft_parse(t_minishell *sh)
{
    long    i;

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

void    ft_minishell_error(t_minishell *sh)
{
    if (sh->ret == -1)
        printf("Erro ao carregar a estrutura. O programa será encerrado agora!\n");
    if (sh->ret == -2)
        printf("readline retornou nulo e o programa será encerrado agora!\n");
    else if (sh->ret == -3)
        printf("split retornou error e o programa será encerrado agora!\n");  
}

void    ft_init_var(t_minishell *sh)
{
    int i;

    i = 0;
    sh->running = TRUE;
    sh->ret = 0;
    sh->parse_len = 0;
    sh->path = NULL;
    sh->pwd = NULL;
    sh->line = NULL;
    sh->parse_str = NULL;
    while (sh->env[i] && (sh->ret == 0))
    {
        if (ft_strncmp(sh->env[i], "PWD", 3) == 0)
        {
            sh->pwd = ft_strdup((sh->env[i]+4));
            if (!sh->pwd)
                sh->ret = -1;
        }
        else if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
        {
            sh->path = ft_strdup((sh->env[i]+5));
            if (!sh->path)
                sh->ret = -1;
        }
        i++;
    }
    if (sh->ret < 0)
        sh->running = FALSE;
}

void ft_minishell(char **envp)
{
    t_minishell sh;

    sh.env = envp;
    ft_init_var(&sh);
    while (sh.running && (sh.ret == 0))
    {
        sh.line = readline("(Minishell - 42Rio): ");
        if (!sh.line)
            sh.ret = -2;
        else
        {
            add_history(sh.line);
            ft_parse(&sh);
            if (sh.parse_len == -1)
                sh.ret = -3;
            else
            {
                long i = 0;
                while(i < sh.parse_len)
                {
                    printf("comando %li recebido da split: %s\n", i, sh.parse_str[i]);
                    if ((ft_strncmp(sh.parse_str[i], "exit", 4) == 0) && (!sh.parse_str[i][4]))
                        sh.running = FALSE;
                    i++;
                }
                ft_free_minishell(&sh, 1);
            }
            ft_free_minishell(&sh, 0);
        }
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh);
    ft_free_minishell(&sh, 2);
    rl_clear_history();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    ft_minishell(envp);
    return (0);
}