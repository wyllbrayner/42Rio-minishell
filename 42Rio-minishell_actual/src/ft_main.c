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

void ft_minishell(void);

void    ft_exec_token(t_minishell *sh);

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
    {
        sh.ret = -7;
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

//        printf("Dentro da minishell | dentro do loop\n");
//        sh.cwd = getcwd(NULL, 0);
//        ft_strlcat(sh.cwd, ":> ", ft_strlen(sh.cwd) + 4);
//        sh.line = readline(sh.cwd);

void ft_minishell(void)
{
    while (sh.running && (sh.ret == 0))
    {
//        signal(SIGINT, &ft_sigint_handler);
//        signal(SIGQUIT, &ft_sigquit_handler);
        sh.line = readline("(Minishell - 42Rio): ");
        if (!sh.line)
            sh.line = ft_strdup("exit");
        add_history(sh.line); /// alterar a posição do history para após da validação do comando para enter/espaço.
        ft_parse(&sh);
        if (sh.ret < 0)
       		ft_minishell_error(&sh);
        else
        {
            ft_exec_token(&sh);
       		ft_minishell_error(&sh);
        }
        ft_free_minishell(&sh, 1);
    }
    if (sh.ret < 0)
        ft_minishell_error(&sh);
    ft_free_minishell(&sh, 2);
}

void    ft_exec_token(t_minishell *sh)
{
    t_node *head;
//    t_node *prev;

    head = sh->head;
    while (head && (sh->ret == 0))
    {
//            printf("nó [token    ]: %s\n", head->token);
//            printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//            printf("nó [first cmd]: %s\n", head->first_cmd);
        if (head->first_cmd[0] != '|')
        {
//            printf("Chama a função correspondente para %s\n", head->first_cmd);
            ft_select_way(sh, head);
            if (sh->ret <= -4)
           		ft_minishell_error(sh);
        }
//        else
//            printf("Pula o '|' \n");
        head = head->next;
    }
}

void    ft_select_way(t_minishell *sh, t_node *node)
{
    if (sh && node)
    {
        if (ft_strncmp(node->first_cmd, "echo", 5) == 0)
        {
            printf("Chama a builtin echo\n");
//            ft_builtin_echo(sh, node);
            ft_builtin_echo(node->token);
//            ft_builtin_echo(sh->line);
        }
        else if (ft_strncmp(node->first_cmd, "cd", 3) == 0)
        {
            printf("Chama a builtin cd\n");
            ft_builtin_cd(sh, node);
        }
        else if (ft_strncmp(node->first_cmd, "pwd", 4) == 0)
        {
            printf("Chama a builtin pwd\n");
            ft_builtin_pwd(sh);
        }
        else if (ft_strncmp(node->first_cmd, "export", 7) == 0)
        {
            printf("Chamar a builtin export\n");
            ft_builtin_export(sh, node);
        }
        else if (ft_strncmp(node->first_cmd, "unset", 6) == 0)
        {
            printf("Chamar a builtin unset\n");
            ft_builtin_unset(sh, node);
        }
        else if (ft_strncmp(node->first_cmd, "env", 4) == 0)
        {
            printf("Chamar a builtin env\n");
            ft_builtin_env(sh, node);
        }
        else if (ft_strncmp(node->first_cmd, "exit", 5) == 0)
        {
            printf("Chamar a builtin exit\n");
            ft_builtin_exit(sh, node);
        }
        else
        {
            printf("Builtin NÃO IDENTIFICADA | procurar dentre as bin\n");
            int rato;
            rato = 0;
            ft_start_command(sh, &rato, node);
            wait(NULL);
        }
    }
    else
        printf("sh->parse não inicializado\n");     
}

/*
void    ft_select_way(t_minishell *sh)
{
    if (sh->parse_str)
    {
        if (ft_strncmp(sh->parse_str[0], "echo", 5) == 0)
            ft_builtin_echo(sh->line);
        else if (ft_strncmp(sh->parse_str[0], "cd", 3) == 0)
            ft_builtin_cd(sh);
        else if (ft_strncmp(sh->parse_str[0], "pwd", 4) == 0)
            ft_builtin_pwd(sh);
        else if (ft_strncmp(sh->parse_str[0], "export", 7) == 0) //depois retornar para 7
        {
            printf("Chamar a função builtin export\n");
            ft_builtin_export(sh);
        }
        else if (ft_strncmp(sh->parse_str[0], "unset", 6) == 0)
        {
            printf("Chamar a função builtin unset\n");
            ft_builtin_unset(sh);
        }
        else if (ft_strncmp(sh->parse_str[0], "env", 4) == 0)
            ft_builtin_env(sh);
        else if (ft_strncmp(sh->parse_str[0], "exit", 5) == 0)
            ft_builtin_exit(sh);
        else
        {
            int rato;
            rato = 0;
            ft_start_command(sh, &rato);
            wait(NULL);
        }
    }
    else
        printf("sh->parse não inicializado\n");     
}
*/



/*
void ft_sigint_handler(int sig)
{
    sh.s_int = FALSE;
    printf("(Minishell - 42Rio): ^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

/*
void ft_sigquit_handler(int sig)
{
    printf("(Minishell - 42Rio): ^D\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/