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
