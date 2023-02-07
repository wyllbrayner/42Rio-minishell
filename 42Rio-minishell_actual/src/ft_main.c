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

t_minishell sh;

//        sh->line = "ls -la Makefile src/ft_main.c | grep main | cat src/ft_parse.c";
//        sh->line = "ls -la Makefile src/ft_main.c | grep main | | src/ft_parse.c";
//        sh->line = "ls -la Makefile src/ft_main.c | grep main | src/ft_parse.c";

void ft_sigint_handler(int sig)
{
    sh.s_int = 1;
    printf("(Minishell - 42Rio): ^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
/*
*/

/*
void ft_sigquit_handler(int sig)
{
    printf("(Minishell - 42Rio): ^C+'\'\n");
//    printf("(Minishell - 42Rio): ^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

void ft_minishell(void)
{
    while (sh.running && (sh.ret == 0))
    {
//        printf("Dentro da minishell | dentro do loop\n");
//        sh.cwd = getcwd(sh.buff, 1024);
//        ft_strlcat(sh.cwd, ":> ", ft_strlen(sh.cwd) + 4);
        signal(SIGINT, &ft_sigint_handler);
//        signal(SIGQUIT, &ft_sigquit_handler);
        sh.line = readline("(Minishell - 42Rio): ");
//        sh.line = readline(sh.cwd);
        if (!sh.line)
        {
            sh.line = ft_strdup("exit");
            add_history(sh.line);
            ft_parse(&sh);
            if (sh.ret < 0)
           		ft_minishell_error(&sh);
            else
                ft_select_way(&sh);
            ft_free_minishell(&sh, 1);
        }
        else
        {
            add_history(sh.line);
            ft_parse(&sh);
            if (sh.ret < 0)
           		ft_minishell_error(&sh);
            else
                ft_select_way(&sh);
            ft_free_minishell(&sh, 1);
        }
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh);
    ft_free_minishell(&sh, 2);
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
    {
        sh.ret = -2;
        sh.erro = argv[1];
        ft_minishell_error(&sh);
    }
    else
    {
        ft_init_var(&sh, envp);
        if (sh.ret < 0)
        {
            ft_minishell_error(&sh);
            ft_free_minishell(&sh, 2);
        }
        else
            ft_minishell();
    }
    return (0);
}
