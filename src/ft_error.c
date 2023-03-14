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

//	printf("ft_minishell_error  - Início\n");
//	printf("ft_minishell_error  - Fim\n");
//	echo $?

static void	ft_minishell_error_aux_0(t_minishell *sh);
static void	ft_minishell_error_aux_1(t_minishell *sh);

void	ft_minishell_error(t_minishell *sh)
{
	if (sh->ret >= -6 && sh->ret <= -1)
		ft_minishell_error_aux_0(sh);
	else if (sh->ret < -6)
		ft_minishell_error_aux_1(sh);
	sh->ret = 0;
	sh->erro = (void *)0;
}

static void	ft_minishell_error_aux_0(t_minishell *sh)
{
	if (sh->ret == -1)
		ft_printf("(Minishell): Unexpected error\n");
	else if ((sh->ret == -3) || (sh->ret == -8))
		;
	else if (sh->ret == -4)
		ft_printf("(Minishell): %s: Command not found\n", sh->erro);
	else if (sh->ret == -5)
		ft_printf("(Minishell): Error: unclosed quotes\n");
	else if (sh->ret == -6)
	{
		if (!sh->erro)
			ft_printf("(Minishell): syntax error near unexpected \
					token `newline'\n");
		else
			ft_printf("(Minishell): syntax error near unexpected \
					token `%s'\n", sh->erro);
	}
}

static void	ft_minishell_error_aux_1(t_minishell *sh)
{
	if (sh->ret == -7)
		ft_printf("(Minishell): %s: No such file or directory\n", sh->erro);
	else if (sh->ret == -9)
		ft_printf("(Minishell): %s: too many arguments\n", sh->erro);
	else if (sh->ret == -10)
		ft_printf("(Minishell): \'%s\': not a valid identifier\n", sh->erro);
	else if (sh->ret == -11)
		ft_printf("(Minishell): %s: numeric argument required\n", sh->erro);
}

/*
void	ft_minishell_error(t_minishell *sh)
{
	if (sh->ret == -1)
		ft_printf("(Minishell): Unexpected error\n");
	else if ((sh->ret == -3) || (sh->ret == -8))
		;
	else if (sh->ret == -4)
		ft_printf("(Minishell): %s: Command not found\n", sh->erro);
	else if (sh->ret == -5)
		ft_printf("(Minishell): Error: unclosed quotes\n");
	else if (sh->ret == -6)
	{
		if (!sh->erro)
			ft_printf("(Minishell): syntax error near unexpected token `newline'\n");
		else
			ft_printf("(Minishell): syntax error near unexpected token `%s'\n", sh->erro);
	}
	else if (sh->ret == -7)
		ft_printf("(Minishell): %s: No such file or directory\n", sh->erro);
	else if (sh->ret == -9)
		ft_printf("(Minishell): %s: too many arguments\n", sh->erro);
	else if (sh->ret == -10)
		ft_printf("(Minishell): \'%s\': not a valid identifier\n", sh->erro);
	else if (sh->ret == -11)
		ft_printf("(Minishell): %s: numeric argument required\n", sh->erro);
	sh->ret = 0;
	sh->erro = (void *)0;
}
*/
