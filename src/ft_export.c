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

static void	ft_builtin_export_aux0(t_minishell *sh, t_node *node, long *var);
static void	ft_builtin_export_aux1(t_minishell *sh, t_node *node, long *var);
static void	ft_builtin_export_aux2(t_minishell *sh, t_node *node, long *var);
static void	ft_builtin_export_aux3(t_minishell *sh, t_node *node, long *var);

void	ft_builtin_export(t_minishell *sh, t_node *node)
{
	long	var[3];

	if (node->cmd[1])
	{
		ft_single_and_double_quotes(sh, node, "export ");
		var[1] = ft_strchr_i(node->cmd[1], '=');
		ft_builtin_export_aux0(sh, node, var);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		var[0] = 0;
		while (sh->env[var[0]])
			ft_printf("declare -x %s\n", sh->env[var[0]++]);
	}
	g_sig.errnbr = 0;
}

static void	ft_builtin_export_aux0(t_minishell *sh, t_node *node, long *var)
{
	if (var[1])
	{
		ft_builtin_export_aux1(sh, node, var);
		if (var[2])
			ft_builtin_export_aux2(sh, node, var);
		else
		{
			ft_builtin_export_aux3(sh, node, var);
			if (sh->ret < 0)
				return ;
		}
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
		sh->tmp3 = NULL;
	}
}

static void	ft_builtin_export_aux1(t_minishell *sh, t_node *node, long *var)
{
	sh->tmp1 = ft_substr(node->cmd[1], 0, (var[1] + 1));
	var[0] = 0;
	var[2] = FALSE;
	while (sh->env[var[0]])
	{
		if (ft_strncmp(sh->env[var[0]], sh->tmp1, (var[1] + 1)) == 0)
		{
			var[2] = TRUE;
			break ;
		}
		var[0]++;
	}
}

static void	ft_builtin_export_aux2(t_minishell *sh, t_node *node, long *var)
{
	ft_free_minishell_single_aux(sh->env[var[0]]);
	sh->env[var[0]] = NULL;
	sh->env[var[0]] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1]));
}

static void	ft_builtin_export_aux3(t_minishell *sh, t_node *node, long *var)
{
	var[0]++;
	sh->tmp3 = (char **)malloc(sizeof(char *) * (++var[0]));
	if (!sh->tmp3)
	{
		g_sig.errnbr = errno;
		ft_free_minishell_single_aux(sh->tmp1);
		sh->ret = -3;
		return ;
	}
	sh->tmp3[--var[0]] = NULL;
	sh->tmp3[--var[0]] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1]));
	while (--var[0] >= 0)
	{
		sh->tmp3[var[0]] = sh->env[var[0]];
		sh->env[var[0]] = NULL;
	}
	ft_free_minishell_double_aux(sh->env);
	sh->env = NULL;
	sh->env = sh->tmp3;
}
