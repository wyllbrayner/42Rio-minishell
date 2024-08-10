/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_var_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

void	ft_expand_variable_0_aux_04(t_minishell *sh, long *var)
{
	var[1] = ft_strlen(sh->tmp1);
	var[0] = 0;
	var[3] = FALSE;
	ft_unset_aux_1(sh, var);
	if (var[3])
	{
		var[4] = ft_strchr_i(sh->env[var[2]], '=');
		sh->tmp5 = ft_substr(sh->env[var[2]], (var[4] + 1), \
		ft_strlen(sh->env[var[2]]) - var[4]);
	}
	else
	{
		if (ft_strncmp(sh->tmp1, "?=", 3) == 0)
			sh->tmp5 = ft_itoa(g_sig.errnbr);
		else
			sh->tmp5 = ft_strdup("");
	}
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
}

void	ft_expand_variable_0_aux_05(t_minishell *sh)
{
	if (!sh->tmp5)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp0, sh->tmp5);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
	}
	sh->tmp5 = sh->tmp1;
	sh->tmp1 = NULL;
}
