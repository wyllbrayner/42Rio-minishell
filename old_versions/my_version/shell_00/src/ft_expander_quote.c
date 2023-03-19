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

static void	ft_expander_dquote(t_minishell *sh, t_node *node);
static void	ft_expander_squote(t_minishell *sh, t_node *node);
static void	ft_expander_squote_aux_0(t_minishell *sh, t_node *node, long *var);

void	ft_expander_quote(t_minishell *sh, t_node *node)
{
	ft_expander_dquote(sh, node);
	if (sh->ret < 0)
		return ;
	ft_expander_squote(sh, node);
	if (sh->ret < 0)
		return ;
}

static void	ft_expander_dquote(t_minishell *sh, t_node *node)
{
	long	i;
	long	j;

	i = 0;
	j = 0;
	sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1));
	if (!sh->tmp1)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
	}
	else
	{
		while (node->token[i])
		{
			if (node->token[i] != '\"')
				sh->tmp1[j++] = node->token[i];
			i++;
		}
		sh->tmp1[j] = '\0';
		ft_builtin_cd_aux_2(sh, node);
	}
}

static void	ft_expander_squote(t_minishell *sh, t_node *node)
{
	long	var[3];

	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1));
	if (!sh->tmp1)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
	}
	else
	{
		ft_expander_squote_aux_0(sh, node, var);
		sh->tmp1[var[1]] = '\0';
		ft_builtin_cd_aux_2(sh, node);
	}
}

static void	ft_expander_squote_aux_0(t_minishell *sh, t_node *node, long *var)
{
	while (node->token[var[0]])
	{
		while (node->token[var[0]])
		{
			if (node->token[var[0]] == '\'')
			{
				var[0]++;
				var[2]++;
			}
			else
				break ;
		}
		if (var[2] % 2)
			sh->tmp1[var[1]++] = '\'';
		var[2] = 0;
		while (node->token[var[0]])
		{
			if (node->token[var[0]] != '\'')
				sh->tmp1[var[1]++] = node->token[var[0]];
			else
				break ;
			var[0]++;
		}
	}
}
