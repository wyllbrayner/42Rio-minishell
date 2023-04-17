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

static void	ft_isexec_aux0(t_minishell *sh, t_node *node);
static void	ft_isexec_aux1(t_minishell *sh, t_node *node);
static void	ft_isexec_aux2(t_minishell *sh, t_node *node);

void	ft_isexec(t_minishell *sh, t_node *node)
{
	if (node->first_cmd[0] == '.')
	{
		ft_isexec_aux0(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else if (ft_strchr("/", node->first_cmd[0]))
	{
		ft_isexec_aux1(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		ft_isexec_aux2(sh, node);
		if (sh->ret < 0)
			return ;
	}
	if (access(node->path, X_OK | F_OK) == -1)
	{
		sh->ret = -4;
		g_sig.errnbr = 127;
		sh->erro = node->first_cmd;
	}
}

static void	ft_isexec_aux0(t_minishell *sh, t_node *node)
{
	if ((int)ft_strchr_i(node->token, '/') == -1)
	{
		sh->ret = -4;
		g_sig.errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
	node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
	if (!node->path)
	{
		sh->ret = -4;
		g_sig.errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}

static void	ft_isexec_aux1(t_minishell *sh, t_node *node)
{
	node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
	if (!node->path)
	{
		sh->ret = -4;
		g_sig.errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}

static void	ft_isexec_aux2(t_minishell *sh, t_node *node)
{
	node->path = ft_access_command(sh, node);
	if (!node->path)
	{
		sh->ret = -4;
		g_sig.errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}
