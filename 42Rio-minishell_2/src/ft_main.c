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
    printf("Dentro da init var | inicio\n");
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
        sh->cwd = NULL;
        sh->buff[PATH_MAX + 1];
        sh->path = NULL;
        sh->line = NULL;
        sh->env = NULL;
        sh->parse_str = NULL;
        sh->erro = NULL;
        sh->lstcmd = NULL;
        sh->tmp1 = NULL;
        sh->tmp2 = NULL;
        sh->tmp3 = NULL;
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
        sh->lstcmd = ft_list_create();
    }
    else
        sh->ret = -1;
    if (sh->ret < 0)
        sh->running = FALSE;
    printf("Dentro da init var | fim\n");
}

void ft_minishell(t_minishell *sh)
{
    printf("Dentro da minishell | inicio\n");
    while (sh->running && (sh->ret == 0))
    {
        printf("Dentro da minishell | dentro do loop\n");
        sh->cwd = getcwd(sh->buff, PATH_MAX);
        ft_strlcat(sh->cwd, ":> ", ft_strlen(sh->cwd) + 4);
//        sh->line = readline("(Minishell - 42Rio): ");
        sh->line = readline(sh->cwd);
        if (!sh->line)
            sh->ret = -3;
        else
        {
            add_history(sh->line);
            printf("Dentro da minishell | chama a ft_parse\n");
            ft_parse(sh);
            printf("Dentro da minishell | retorno da ft_parse\n");
            if (sh->ret < 0)
           		ft_minishell_error(sh);
            else
            {
                printf("Dentro da minishell | chama a select_way\n");
                ft_select_way(sh);
                printf("Dentro da minishell | retorno da select_way\n");
            }
            printf("Dentro da minishell | chama a free minishell (1)\n");
            ft_free_minishell(sh, 1);
            printf("Dentro da minishell | retorno da free minishell (1)\n");
        }
    }
    if (sh->ret < 0)
        ft_minishell_error(sh);
    ft_free_minishell(sh, 2);
    printf("Dentro da minishell | fim\n");
}

int main(int argc, char **argv, char **envp)
{
//    printf("Dentro da main | inicio\n");
    if (argc != 1)
    {
//        printf("Dentro da main | 1° if\n");
        sh.ret = -2;
        sh.erro = argv[1];
        ft_minishell_error(&sh);
    }
    else
    {
//        printf("Dentro da main | 2° if | Antes de init var\n");
        ft_init_var(&sh, envp);
/*
        long i = 0;
        printf("Dentro da main | 2° if | Após a inicialização | conteúdo de env\n");
        while (sh.env[i])
        {
            printf("%s\n", sh.env[i]);
            i++;
        }
        i = 0;
        printf("Dentro da main | 2° if | Após a inicialização | conteúdo de path\n");
        while (sh.path[i])
        {
            printf("%s\n", sh.path[i]);
            i++;
        }
*/
        printf("Dentro da main | 2° if | chama a ft_minishell\n");
        ft_minishell(&sh);
        printf("Dentro da main | 2° if | retorno da ft_minishell\n");
    }
    printf("Dentro da main | fim\n");
    return (0);
}

/*
//void new_line_handler(void)
//{
//    printf("New Line created\n");
//}
//new_line_handler(); // na main!!

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
*/