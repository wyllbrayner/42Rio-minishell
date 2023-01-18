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

void    ft_parse_comand_is_valid(t_minishell *sh)
{
    long    i;

    i = 0;
    while (sh->parse_str[i])
    {
        if ((ft_strncmp(sh->parse_str[i], "|", 1) == 0) || (ft_strncmp(sh->parse_str[i], "<", 1) == 0) || (ft_strncmp(sh->parse_str[i], "<<", 2) == 0) || (ft_strncmp(sh->parse_str[i], ">", 1) == 0) || (ft_strncmp(sh->parse_str[i], ">>", 2) == 0))
            printf("%s     é um PIPE ou > ou <\n", sh->parse_str[i]);
        else
            printf("%s não é um PIPE ou > ou <\n", sh->parse_str[i]);
        i++;        
    }

// int access(const char *pathname, int mode);
// F_OK, R_OK, W_OK, X_OK
}

void ft_parse(t_minishell *sh)
{
    sh->parse_str = ft_split(sh->line, ' ');
//    ft_parse_comand_is_valid(sh);
}

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

void    ft_init_var(t_minishell *sh)
{
    long i;

    i = 0;
    sh->running = TRUE;
    sh->ret = 0;
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
            sh->path = ft_split(sh->env[i]+5, ':');
            if (!sh->path)
                sh->ret = -1;
        }
        i++;
    }
    if (sh->ret < 0)
        sh->running = FALSE;
}

void    ft_select_way(t_minishell *sh)
{
    if ((ft_strncmp(sh->parse_str[0], "echo", 4) == 0) && (!sh->parse_str[0][4]))
        printf("Chamar a função builtin echo\n");
    else if ((ft_strncmp(sh->parse_str[0], "pwd", 3) == 0) && (!sh->parse_str[0][3]))
        printf("Chamar a função builtin pwd\n");
    else if ((ft_strncmp(sh->parse_str[0], "env", 3) == 0) && (!sh->parse_str[0][3]))
        printf("Chamar a função builtin env\n");
    else if ((ft_strncmp(sh->parse_str[0], "cd", 2) == 0) && (!sh->parse_str[0][2]))
        printf("Chamar a função builtin cd\n");
    else if ((ft_strncmp(sh->parse_str[0], "export", 6) == 0) && (!sh->parse_str[0][6]))
        printf("Chamar a função builtin export\n");
    else if ((ft_strncmp(sh->parse_str[0], "unset", 5) == 0) && (!sh->parse_str[0][5]))
        printf("Chamar a função builtin unset\n");
    else if ((ft_strncmp(sh->parse_str[0], "bash", 4) == 0) && (!sh->parse_str[0][4]))
        printf("Chamar a função builtin bash\n");
    else if (ft_strncmp(sh->parse_str[0], "exit", 4) == 0)
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
            if (!sh.parse_str)
                sh.ret = -3;
            else
            {
/*
                long i = 0;
                while(sh.parse_str[i] && sh.running)
                {
                    printf("comando %li recebido da split: %s\n", i, sh.parse_str[i]);
                    i++;
                }
*/
                ft_select_way(&sh);
            }
            ft_free_minishell(&sh, 1);
        }
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh, NULL);
    ft_free_minishell(&sh, 2);
//    rl_clear_history();
    clear_history();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    ft_minishell(envp);
    return (0);
}