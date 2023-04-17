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

static void	ft_expand_variable_1_aux_00(t_node *node, long *var);
static void	ft_expand_variable_1_aux_01(t_minishell *sh, t_node *node, \
		long *var);
static void	ft_expand_variable_1_aux_02(t_node *node, long *var);

void	ft_expand_variable(t_minishell *sh, t_node *node)
{
	long	var[7];

	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	var[3] = 0;
	var[4] = 0;
	var[5] = 0;
	var[6] = FALSE;
	while (node->token[var[5]] && !ft_isspace(node->token[var[5]]))
		var[5]++;
	while (node->token[var[5]] && ft_isspace(node->token[var[5]]))
		var[5]++;
	while (node->token[var[5]])
	{
		ft_expand_variable_1_aux_00(node, var);
		ft_expand_variable_1_aux_01(sh, node, var);
		if (sh->ret < 0)
			return ;
		ft_expand_variable_1_aux_02(node, var);
	}
}

static void	ft_expand_variable_1_aux_00(t_node *node, long *var)
{
	while (node->token[var[5]] && !(ft_strchr("$~", node->token[var[5]])))
	{
		if (node->token[var[5]] == '\'')
		{
			if (var[6])
				var[6] = 0;
			else
				var[6] = TRUE;
		}
		var[5]++;
	}
}

static void	ft_expand_variable_1_aux_01(t_minishell *sh, t_node *node, \
		long *var)
{
	if (node->token[var[5]] && var[6])
	{
		while (node->token[var[5]] && node->token[var[5]] != '\'')
			var[5]++;
		var[6] = FALSE;
	}
	else
	{
		ft_expand_variable_0(sh, node, var);
		if (sh->ret < 0)
			return ;
		var[0] = var[5];
		if (node->token[var[5]] == '\'')
		{
			if (var[6])
				var[6] = 0;
			else
				var[6] = TRUE;
		}
	}
}

static void	ft_expand_variable_1_aux_02(t_node *node, long *var)
{
	if (node->token[var[5]])
	{
		if (node->token[var[5]] != '~')
			var[5]++;
		else
		{
			var[5]++;
			var[0] = var[5];
		}
	}
}
