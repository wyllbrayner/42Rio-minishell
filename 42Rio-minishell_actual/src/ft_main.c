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

void    ft_init_var(t_minishell *sh, char **envp)
{
    long    i;

    if (sh && envp)
    {
        i = 0;
        sh->ret = 0;
        sh->out_redirect = 0;
        sh->out_redirect_file = NULL;
        sh->out_redirect_file_fd = NULL;
        sh->out_redirect_file_fd_amount = 0;
        sh->in_redirect = 0;
        sh->in_redirect_file = NULL;
        sh->in_redirect_file_fd = NULL;
        sh->in_redirect_file_fd_amount = 0;
        sh->running = TRUE;
        sh->s_int = FALSE;
//        sh->cwd = NULL;
//        sh->buff[1024];
        sh->path = NULL;
        sh->line = NULL;
        sh->env = NULL;
        sh->parse_str = NULL;
        sh->erro = NULL;
        sh->head = NULL;
        sh->tmp1 = NULL;
        sh->tmp2 = NULL;
        sh->tmp3 = NULL;
        sh->tmp4 = NULL;
        while (envp[i])
            i++;
        sh->env = (char **)malloc(sizeof(char *) * (++i));
        if (!sh->env)
            sh->ret = -3;
        else
        {
            --i;
            sh->env[i] = NULL;
            while ((--i >= 0) && (sh->ret == 0))
            {
                sh->env[i] = ft_strdup(envp[i]);
                if (!sh->env[i])
                    sh->ret = -3;
                else
                {
                    if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
                    {
                        sh->path = ft_split(sh->env[i] + 5, ':');
                        if (!sh->path)
                            sh->ret = -3;
                    }
                }
            }
        }
    }
    else
        sh->ret = -1;
}

void ft_minishell(t_minishell *sh)
{
    while (sh->running && (sh->ret == 0))
    {
//        printf("Dentro da minishell | dentro do loop\n");
//        sh->cwd = getcwd(sh->buff, 1024);
//        ft_strlcat(sh->cwd, ":> ", ft_strlen(sh->cwd) + 4);
        sh->line = readline("(Minishell - 42Rio): ");
//        sh->line = readline(sh->cwd);
//        sh->line = "ls -la Makefile src/ft_main.c | grep main | cat src/ft_parse.c";
//        sh->line = "ls -la Makefile src/ft_main.c | grep main | | src/ft_parse.c";
//        sh->line = "ls -la Makefile src/ft_main.c | grep main | src/ft_parse.c";
        if (!sh->line)
            sh->ret = -3;
        else
        {
            add_history(sh->line);
            ft_parse(sh);
            if (sh->ret < 0)
           		ft_minishell_error(sh);
            else
                ft_select_way(sh);
            ft_free_minishell(sh, 1);
        }
    }
    if (sh->ret < 0)
        ft_minishell_error(sh);
    ft_free_minishell(sh, 2);
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
            ft_minishell(&sh);
    }
    return (0);
}
