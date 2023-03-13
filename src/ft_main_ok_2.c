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

t_minishell	sh;

//        sh.cwd = getcwd(NULL, 0);
//        ft_strlcat(sh.cwd, ":> ", ft_strlen(sh.cwd) + 4);
//        sh.line = readline(sh.cwd);

void	ft_minishell(void);
void	ft_exec_token(t_minishell *sh);

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		sh.ret = -7;
		sh.erro = argv[1];
		ft_minishell_error(&sh);
		sh.errnbr = 127;
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

//        if (RL_ISSTATE(RL_STATE_READCMD))
//            ioctl(STDIN_FILENO, TIOCSTI, "\n");
void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		sh.s_int = FALSE;
		sh.errnbr = 130;
		sh.tmp0 = NULL;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_signal(void)
{
	signal(SIGINT, &ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_minishell(void)
{
	while (sh.running && (sh.ret == 0))
	{
		ft_handle_signal();
		sh.line = readline("(Minishell - 42Rio): ");
		if (!sh.line)
		{
			sh.s_int = 2;
			sh.line = ft_strdup("exit");
		}
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

//    printf("ft_exec_token  - Início\n");    
//        printf("nó [token    ]: %s\n", head->token);
//        printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//        printf("nó [first cmd]: %s\n", head->first_cmd);
//          printf("Para token: %s o retorno atual é: %d\n", head->token, sh->errnbr);
//            printf("Para token: %s o retorno atual é: %d\n", head->token, sh->errnbr);
//                printf("Chama a função correspondente para %s\n", head->first_cmd);
//                    printf("Chama a função correspondente para %s\n", head->first_cmd);
//        printf("Para token: %s o retorno atual é: %d\n", head->token, sh->errnbr);
//    printf("ft_exec_token  - Fim\n");
void	ft_exec_token(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && head->first_cmd[0] != '>')
		{
			ft_expander_quote(sh, head);
			ft_expander_variable(sh, head);
			if (!head->prev)
			{
				ft_select_way(sh, head);
				if (sh->ret <= -4)
					ft_minishell_error(sh);
			}
			if (head->prev)
			{
				if (head->prev->first_cmd[0] != '<' && head->prev->first_cmd[0] != '>')
				{
					ft_select_way(sh, head);
					if (sh->ret <= -4)
						ft_minishell_error(sh);
				}
			}
		}
		head = head->next;
	}
}

//            printf("Chama a builtin echo\n");
//            printf("Chama a builtin cd\n");
//            printf("Chama a builtin pwd\n");
//            printf("Chamar a builtin export\n");
//            printf("Chamar a builtin unset\n");
//            printf("Chamar a builtin env\n");
//            printf("Chamar a builtin exit\n");
//            printf("Builtin NÃO IDENTIFICADA | procurar dentre as bin\n");
void	ft_select_way(t_minishell *sh, t_node *node)
{
	if (sh && node)
	{
		if (ft_strncmp(node->first_cmd, "echo", 5) == 0)
			ft_builtin_echo(sh, node);
		else if (ft_strncmp(node->first_cmd, "cd", 3) == 0)
			ft_builtin_cd(sh, node);
		else if (ft_strncmp(node->first_cmd, "pwd", 4) == 0)
			ft_builtin_pwd(sh);
		else if (ft_strncmp(node->first_cmd, "export", 7) == 0)
			ft_builtin_export(sh, node);
		else if (ft_strncmp(node->first_cmd, "unset", 6) == 0)
			ft_builtin_unset(sh, node);
		else if (ft_strncmp(node->first_cmd, "env", 4) == 0)
			ft_builtin_env(sh, node);
		else if (ft_strncmp(node->first_cmd, "exit", 5) == 0)
			ft_builtin_exit(sh, node);
		else
		{
			int	rato;
			rato = 0;
			ft_start_command(sh, &rato, node);
			wait(NULL);
		}
	}
}
