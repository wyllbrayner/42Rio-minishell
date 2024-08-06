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

static void	ft_heredoc_build_list(t_minishell *sh, t_node *node);
static void	ft_heredoc_build_list_aux0(t_minishell *sh, t_node *node);
static void	ft_heredoc_expand_var(t_minishell *sh);
static void	ft_heredoc_expand_var_aux0(t_minishell *sh, t_node *node);

void	ft_heredoc_builder(t_minishell *sh, t_node *node)
{
	sh->head_tmp = NULL;
	ft_heredoc_build_list(sh, node);
	if (sh->ret < 0)
	{
		ft_list_destroy(&sh->head_tmp);
		return ;
	}
	ft_heredoc_expand_var(sh);
	if (sh->ret < 0)
	{
		ft_list_destroy(&sh->head_tmp);
		return ;
	}
	ft_heredoc_fd(sh, node);
	if (sh->ret < 0)
	{
		ft_list_destroy(&sh->head_tmp);
		return ;
	}
	ft_list_destroy(&sh->head_tmp);
	sh->head_tmp = NULL;
}

static void	ft_heredoc_build_list(t_minishell *sh, t_node *node)
{
	sh->tmp0 = readline("(42Rio) > ");
	if (sh->tmp0)
	{
		ft_heredoc_build_list_aux0(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else
		sh->ret = -3;
}

static void	ft_heredoc_build_list_aux0(t_minishell *sh, t_node *node)
{
	while ((ft_strncmp(sh->tmp0, node->token, \
	(ft_strlen(node->token) + 1)) != 0) && g_sig.s_int == 1)
	{
		sh->tmp1 = ft_strjoin(" ", sh->tmp0);
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		if (!sh->tmp1)
		{
			sh->ret = -3;
			g_sig.errnbr = errno;
			return ;
		}
		ft_list_add_last(&sh->head_tmp, ft_node_create(sh->tmp1));
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
		sh->tmp0 = readline("(42Rio) > ");
		if (!sh->tmp0)
			break ;
	}
	if (!sh->tmp0)
		sh->ret = -3;
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	if (g_sig.s_int != 1)
		sh->ret = -3;
}

static void	ft_heredoc_expand_var(t_minishell *sh)
{
	t_node	*node;

	node = sh->head_tmp;
	while (node)
	{
		if (!ft_strchr(node->token, '~'))
		{
			ft_heredoc_expand_var_aux0(sh, node);
			if (sh->ret < 0)
				return ;
		}
		node = node->next;
	}
}

static void	ft_heredoc_expand_var_aux0(t_minishell *sh, t_node *node)
{
	ft_expand_variable(sh, node);
	if (sh->tmp5)
	{
		sh->tmp2 = ft_substr(sh->tmp5, 1, (ft_strlen(sh->tmp5) - 1));
		ft_free_minishell_single_aux(sh->tmp5);
		sh->tmp5 = NULL;
		if (!sh->tmp2)
		{
			sh->ret = -3;
			g_sig.errnbr = errno;
			return ;
		}
		sh->tmp1 = sh->tmp2;
		sh->tmp2 = (void *)0;
		ft_builtin_cd_aux_2(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		sh->ret = -3;
		return ;
	}
}
