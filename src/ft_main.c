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

    i = 0;
    if (sh && envp)
    {
        sh->ret = 0;
        sh->out_redirect = 0;
        sh->out_redirect_file = NULL;
        sh->out_redirect_file_fd = NULL;
        sh->out_redirect_file_fd_amount = 0;
        sh->in_redirect = 0;
        sh->in_redirect_file = NULL;
        sh->in_redirect_file_fd = NULL;
        sh->in_redirect_file_fd_amount = 0;
        sh->running = 1;
        sh->s_int = 0;
        sh->path = NULL;
        sh->line = NULL;
        sh->env = NULL;
        sh->parse_str = NULL;
        sh->erro = NULL;
        sh->tmp1 = NULL;
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
                        sh->path = ft_split(sh->env[i]+5, ':');
                        if (!sh->path)
                            sh->ret = -3;
                    }
                }
            }
        }
    }
    else
        sh->ret = -1;
    if (sh->ret < 0)
        sh->running = F;
}

/*
void new_line_handler(void) {
    printf("New Line created\n");
}
new_line_handler(); // na main!!
*/

void ft_sigint_handler(int sig)
{
    sh.s_int = 1;
    write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ft_minishell(char **envp)
{
//    t_minishell sh;
    char        *cwd;
    char        buff[PATH_MAX + 1];

//    (void **)envp;
//    ft_init_var(&sh, NULL);
    ft_init_var(&sh, envp);
    signal(SIGINT, &ft_sigint_handler);
    while (sh.running && (sh.ret == 0))
    {
        cwd = getcwd(buff, PATH_MAX);
        ft_strlcat(cwd, ":> ", ft_strlen(cwd) + 4);
//        sh.line = readline("(Minishell - 42Rio): ");
        sh.line = readline(cwd);
        if (!sh.line)
            sh.ret = -3;
        else
        {
            add_history(sh.line);
            ft_parse(&sh);
            if (sh.ret < 0)
           		ft_minishell_error(&sh);
            else
            {
                ft_select_way(&sh);
            }
            ft_free_minishell(&sh, 1);
        }
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh);
    ft_free_minishell(&sh, 2);
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    if (argc == 1)
        ft_minishell(envp);
//    else
//        ret = ???;
//        ft_minishell_error(sh, argv[1]);
    return (0);
}
