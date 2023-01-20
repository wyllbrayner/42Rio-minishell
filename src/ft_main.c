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

void    ft_minishell_error(t_minishell *sh, char *str)
{
    if (sh->ret == -1)
        printf("Erro ao carregar a estrutura. O programa será encerrado agora!\n");
    else if (sh->ret == -2)
        printf("readline retornou nulo e o programa será encerrado agora!\n");
    else if (sh->ret == -3)
        printf("split retornou error e o programa será encerrado agora!\n");
    else if (sh->ret == -4)
        printf("(Minishell): %s: command not found\n", str);
    sh->ret = 0;
}

void    ft_select_way(t_minishell *sh)
{
    if (ft_strncmp(sh->parse_str[0], "echo", 5) == 0)
        printf("Chamar a função builtin echo\n");
    else if (ft_strncmp(sh->parse_str[0], "pwd", 4) == 0)
        printf("Chamar a função builtin pwd\n");
    else if (ft_strncmp(sh->parse_str[0], "env", 4) == 0)
        ft_builtin_env(sh, 0);
    else if (ft_strncmp(sh->parse_str[0], "cd", 3) == 0)
        printf("Chamar a função builtin cd\n");
    else if (ft_strncmp(sh->parse_str[0], "export", 7) == 0)
        printf("Chamar a função builtin export\n");
    else if (ft_strncmp(sh->parse_str[0], "unset", 6) == 0)
        printf("Chamar a função builtin unset\n");
    else if (ft_strncmp(sh->parse_str[0], "bash", 5) == 0)
        printf("Chamar a função builtin bash\n");
    else if (ft_strncmp(sh->parse_str[0], "exit", 5) == 0)
        ft_builtin_exit(sh, 0);
    else
    {
    /// JONATAS sugiro colocar sua função a partir daqui!!!
        int rato;
        rato = 0;
        start_command(sh, &rato);
        wait(NULL);
//        waitpid(rato, NULL, 0);
    }
}

void    ft_init_var(t_minishell *sh, char **envp)
{
    long    i;

    i = 0;
    sh->ret = 0;
    sh->running = TRUE;
    sh->path = NULL;
    sh->line = NULL;
    sh->env = NULL;
    sh->parse_str = NULL;
    sh->tmp1 = NULL;
    while (envp[i])
        i++;
    sh->env = (char **)malloc(sizeof(char *) * (++i));
    if (!sh->env)
        sh->ret = -1;
    --i;
    while ((--i >= 0) && (sh->ret == 0))
    {
        sh->tmp1 = ft_strdup(envp[i]);
        if (!sh->tmp1)
            sh->ret = -1;
        else
        {
            sh->env[i] = sh->tmp1;
            sh->tmp1 = NULL;
            if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
            {
                sh->path = ft_split(sh->env[i]+5, ':');
                if (!sh->path)
                    sh->ret = -1;
            }
        }
    }
    if (sh->ret < 0)
        sh->running = FALSE;
}

/*
void new_line_handler(void) {
    printf("New Line created\n");
}
*/

void ft_minishell(char **envp)
{
    t_minishell sh;

    ft_init_var(&sh, envp);
//    new_line_handler();
    while (sh.running && (sh.ret == 0))
    {
        sh.line = readline("(Minishell - 42Rio): ");
        if (!sh.line)
            sh.ret = -2;
        else
        {
            add_history(sh.line);
            ft_parse(&sh);
            if (!sh.parse_str)
                sh.ret = -3;
            else
            {
                long i = -1;
                while(sh.parse_str[++i] && sh.running)
                    printf("comando %li recebido da split: %s\n", i, sh.parse_str[i]);
/*
*/
                ft_select_way(&sh);
            }
            ft_free_minishell(&sh, 1);
        }
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh, NULL);
    ft_free_minishell(&sh, 2);
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    if (argc == 1)
        ft_minishell(envp);
    return (0);
}