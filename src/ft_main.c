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

    if (status == 0)
        ft_free_minishell_aux(sh->line);
    if (status == 1)
    {
        i = 0;
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
        i = 0;
        while (sh->path2[i])
        {
            ft_free_minishell_aux(sh->path2[i]);
            i++;
        }
        free(sh->path2);
        ft_free_minishell_aux(sh->pwd);
    }
}

char *ft_join_path(char const *path, char const *cmd)
{
    char *tmp1;
    char *tmp2;

    tmp1 = NULL;
    tmp2 = NULL;
    tmp1 = ft_strjoin(path, "/");
    if (!tmp1)
        return (NULL);
    tmp2 = ft_strjoin(tmp1, cmd);
    if (!tmp2)
    {
        free(tmp1);
        return (NULL);
    }
    printf("tmp2: %s", tmp2);
    return(tmp2);
}



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
    ft_parse_comand_is_valid(sh);
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
//            sh->path = ft_strdup((sh->env[i]+5));
//            if (!sh->path)
//                sh->ret = -1;
            sh->path2 = ft_split(sh->env[i]+5, ':');
            if (!sh->path2)
                sh->ret = -1;
//            sh->path2 = ft_split(sh->path, ':');
//            if (!sh->path2)
//                sh->ret = -1;
//            ft_free_minishell_aux(sh->path);
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
    int i = 0;
    while (sh.path2[i])
    {
        printf("sh.path2[%i]: %s\n", i, sh.path2[i]);
        i++;
    }
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
                /// JONATAS sugiro colocar sua função a partir daqui!!!
                int rato;
                start_command(&sh, &rato);
                waitpid(rato, NULL, 0);
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
//    rl_clear_history();
//    clear_history();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    ft_minishell(envp);
    return (0);
}