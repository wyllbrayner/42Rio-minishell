/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:06:38 by woliveir          #+#    #+#             */
/*   Updated: 2023/01/24 16:06:38 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

static void	ft_valid_quotes_aux3(t_minishell *sh, t_node *node, long *var);
static void	ft_valid_quotes_aux4(t_minishell *sh, t_node *node, long *var);

void	ft_valid_quotes_aux2(t_minishell *sh, t_node *node, long *var)
{
	if (var[3])
	{
		ft_valid_quotes_aux3(sh, node, var);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		ft_valid_quotes_aux4(sh, node, var);
		if (sh->ret < 0)
			return ;
	}
}

static void	ft_valid_quotes_aux3(t_minishell *sh, t_node *node, long *var)
{
	sh->tmp1 = ft_substr(node->cmd[1], var[1], (var[2] - var[1]));
	if (!sh->tmp1)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
		return ;
	}
	var[3] = FALSE;
}

static void	ft_valid_quotes_aux4(t_minishell *sh, t_node *node, long *var)
{
	sh->tmp2 = ft_substr(node->cmd[1], var[1], (var[2] - var[1]));
	if (!sh->tmp2)
	{
		g_sig.errnbr = errno;
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
		sh->ret = -3;
		return ;
	}
	sh->tmp5 = ft_strjoin(sh->tmp1, sh->tmp2);
	g_sig.errnbr = errno;
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	ft_free_minishell_single_aux(sh->tmp2);
	sh->tmp2 = NULL;
	if (!sh->tmp5)
	{
		sh->ret = -3;
		return ;
	}
	sh->tmp1 = sh->tmp5;
	sh->tmp5 = NULL;
}
