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

extern t_signal	g_sig;

static void	ft_valid_redirect_0(t_minishell *sh);
static void	ft_valid_redirect_0_aux_0(t_minishell *sh, long *var);
static void	ft_valid_redirect_0_aux_1(t_minishell *sh, long *var);
static void	ft_valid_redirect_0_aux_2(t_minishell *sh, long *var);

void	ft_valid_redirect(t_minishell *sh)
{
	ft_valid_redirect_0(sh);
	if (sh->ret < 0)
		return ;
	ft_valid_redirect_1(sh);
	if (sh->ret < 0)
		return ;
}

static void	ft_valid_redirect_0(t_minishell *sh)
{
	long	var[5];

	ft_cmd_builder_init_var(sh->caract, "><", var);
	while (sh->line[var[0]])
	{
		ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
		if (ft_strchr("<>", sh->line[var[0]]) && \
				(ft_strlen(sh->line) - var[0]) >= 3)
		{
			ft_valid_redirect_0_aux_0(sh, var);
			if (sh->ret < 0)
				return ;
			var[0]++;
		}
		else
			break ;
	}
}

static void	ft_valid_redirect_0_aux_0(t_minishell *sh, long *var)
{
	if (var[0] == 0)
	{
		ft_valid_redirect_0_aux_1(sh, var);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		ft_valid_redirect_0_aux_2(sh, var);
		if (sh->ret < 0)
			return ;
	}
}

static void	ft_valid_redirect_0_aux_1(t_minishell *sh, long *var)
{
	if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
	{
		sh->ret = -6;
		sh->erro = ">>>";
		g_sig.errnbr = 258;
	}
	else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
	{
		sh->ret = -6;
		sh->erro = "<<<";
		g_sig.errnbr = 258;
	}
}

static void	ft_valid_redirect_0_aux_2(t_minishell *sh, long *var)
{
	if (!ft_strchr("_-", sh->line[(var[0] - 1)]))
	{
		if (ft_strncmp(&sh->line[var[0]], ">>>", 3) == 0)
		{
			sh->ret = -6;
			sh->erro = ">>>";
			g_sig.errnbr = 258;
		}
		else if (ft_strncmp(&sh->line[var[0]], "<<<", 3) == 0)
		{
			sh->ret = -6;
			sh->erro = "<<<";
			g_sig.errnbr = 258;
		}
	}
}
