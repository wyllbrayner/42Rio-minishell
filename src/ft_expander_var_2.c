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

static void	ft_expand_variable_0_aux_00(t_minishell *sh, t_node *node, \
		long *var);
static void	ft_expand_variable_0_aux_01(t_minishell *sh, t_node *node, \
		long *var);
static void	ft_expand_variable_0_aux_02(t_minishell *sh, t_node *node, \
		long *var);
static void	ft_expand_variable_0_aux_03(t_minishell *sh);

void	ft_expand_variable_0(t_minishell *sh, t_node *node, long *var)
{
	ft_expand_variable_0_aux_01(sh, node, var);
	if (sh->ret < 0)
		return ;
	ft_expand_variable_0_aux_02(sh, node, var);
	ft_expand_variable_0_aux_03(sh);
	if (sh->ret < 0)
		return ;
	ft_expand_variable_0_aux_04(sh, var);
	ft_expand_variable_0_aux_05(sh);
	if (sh->ret < 0)
		return ;
}

static void	ft_expand_variable_0_aux_00(t_minishell *sh, t_node *node, \
		long *var)
{
	sh->tmp0 = ft_substr(node->token, var[0], (var[5] - var[0]));
	if (!sh->tmp0)
	{
		ft_free_minishell_single_aux(sh->tmp5);
		sh->tmp5 = NULL;
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp5, sh->tmp0);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
		return ;
	}
	sh->tmp0 = sh->tmp1;
	sh->tmp1 = NULL;
}

static void	ft_expand_variable_0_aux_01(t_minishell *sh, t_node *node, \
		long *var)
{
	if (!sh->tmp5)
	{
		sh->tmp0 = ft_substr(node->token, var[0], var[5]);
		if (!sh->tmp0)
		{
			g_sig.errnbr = errno;
			sh->ret = -3;
			return ;
		}
	}
	else
	{
		if (node->token[var[0]] != '$')
		{
			ft_expand_variable_0_aux_00(sh, node, var);
			if (sh->ret < 0)
				return ;
		}
		else
		{
			sh->tmp0 = sh->tmp5;
			sh->tmp5 = NULL;
			var[5] = var[0];
		}
	}
}

static void	ft_expand_variable_0_aux_02(t_minishell *sh, t_node *node, \
		long *var)
{
	if (node->token[var[5]])
	{
		if (node->token[var[5]] != '~')
			var[5]++;
	}
	var[0] = var[5];
	while (node->token[var[5]] && !(ft_strchr("/$~\'", node->token[var[5]])) \
		&& !ft_isspace(node->token[var[5]]))
		var[5]++;
	if ((var[0] == var[5]) && (node->token[var[5]] == '~') && \
							(node->token[(var[5] - 1)] == ' '))
	{
		if (!node->token[(var[5] + 1)])
			sh->tmp5 = ft_strdup("HOME");
		else if (((node->token[(var[5] + 1)] == ' ') || \
				(node->token[(var[5] + 1)] == '/')))
			sh->tmp5 = ft_strdup("HOME");
	}
	else
		sh->tmp5 = ft_substr(node->token, var[0], (var[5] - var[0]));
}

static void	ft_expand_variable_0_aux_03(t_minishell *sh)
{
	if (!sh->tmp5)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp5, "=");
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
}
