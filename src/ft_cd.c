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

static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node);
static void	ft_builtin_cd_aux_3(t_minishell *sh, char *str);

void	ft_builtin_cd(t_minishell *sh, t_node *node)
{
	ft_single_and_double_quotes(sh, node, "cd ");
	sh->tmp0 = getcwd(NULL, 0);
	if (!sh->tmp0)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	else
	{
		ft_builtin_cd_aux_1(sh, node);
		if (sh->ret < 0)
			return ;
	}
}

static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node)
{
	if (chdir(node->cmd[1]) == -1)
	{
		sh->ret = -7;
		sh->erro = node->cmd[1];
		g_sig.errnbr = 1;
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
	}
	else
	{
		ft_builtin_cd_aux_3(sh, "export OLDPWD=");
		if (sh->ret < 0)
			return ;
		sh->tmp0 = getcwd(NULL, 0);
		if (!sh->tmp0)
		{
			sh->ret = -3;
			g_sig.errnbr = errno;
			return ;
		}
		ft_builtin_cd_aux_3(sh, "export PWD=");
		if (sh->ret < 0)
			return ;
		g_sig.errnbr = 0;
	}
}

void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node)
{
	ft_free_minishell_single_aux(node->token);
	node->token = NULL;
	node->token = sh->tmp1;
	sh->tmp1 = NULL;
	ft_free_minishell_double_aux(node->cmd);
	node->cmd = NULL;
	node->cmd = ft_split(node->token, ' ');
	if (!node->cmd)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	ft_free_minishell_single_aux(node->first_cmd);
	node->first_cmd = NULL;
	node->first_cmd = ft_strdup(node->cmd[0]);
	if (!node->first_cmd)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
}

static void	ft_builtin_cd_aux_3(t_minishell *sh, char *str)
{
	sh->tmp1 = ft_strjoin(str, sh->tmp0);
	if (!sh->tmp1)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		return ;
	}
	sh->head_tmp = ft_node_create(sh->tmp1);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	ft_builtin_export(sh, sh->head_tmp);
	ft_list_destroy(&sh->head_tmp);
	sh->head_tmp = NULL;
}
