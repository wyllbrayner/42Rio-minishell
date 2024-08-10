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

t_signal	g_sig;

static void	ft_minishell(t_minishell *sh);
static void	ft_handle_signal(void);
static void	ft_sigint_handler(int sig);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;

	if (argc != 1)
	{
		sh.ret = -7;
		sh.erro = argv[1];
		ft_minishell_error(&sh);
		g_sig.errnbr = 127;
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

static void	ft_minishell(t_minishell *sh)
{
	ft_handle_signal();
	while (sh->running && (sh->ret == 0))
	{
		sh->line = readline("(Minishell - 42Rio): ");
		if (!sh->line)
		{
			g_sig.s_int = 2;
			sh->line = ft_strdup("exit");
		}
		ft_parse(sh);
		if (sh->ret < 0)
			ft_minishell_error(sh);
		else
		{
			check_pipe(sh);
			ft_minishell_error(sh);
		}
		ft_free_minishell(sh, 1);
	}
	if (sh->ret < 0)
		ft_minishell_error(sh);
	ft_free_minishell(sh, 2);
}

static void	ft_handle_signal(void)
{
	signal(SIGINT, &ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig.s_int = FALSE;
		g_sig.errnbr = 130;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
