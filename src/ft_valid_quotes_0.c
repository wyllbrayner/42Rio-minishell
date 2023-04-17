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

static void	ft_single_and_double_quotes_aux(t_minishell *sh, t_node *node, \
char *first, int c);
static void	ft_valid_quotes(t_minishell *sh, t_node *node, char *first_c, \
int c);
static void	ft_valid_quotes_aux0(long *var);
static void	ft_valid_quotes_aux1(t_node *node, int c, long *var);

void	ft_single_and_double_quotes(t_minishell *sh, t_node *node, char *first)
{
	ft_single_and_double_quotes_aux(sh, node, first, '\"');
	if (sh->ret < 0)
		return ;
	ft_single_and_double_quotes_aux(sh, node, first, '\'');
	if (sh->ret < 0)
		return ;
}

static void	ft_single_and_double_quotes_aux(t_minishell *sh, t_node *node, \
char *first, int c)
{
	ft_valid_quotes(sh, node, first, c);
	if (sh->ret < 0 || !sh->tmp1)
		return ;
	sh->tmp2 = ft_strjoin(first, sh->tmp1);
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	if (!sh->tmp2)
		return ;
	sh->tmp1 = sh->tmp2;
	sh->tmp2 = NULL;
	ft_builtin_cd_aux_2(sh, node);
	if (sh->ret < 0)
		return ;
}

static void	ft_valid_quotes(t_minishell *sh, t_node *node, char *first_c, int c)
{
	long	var[5];

	if (node->cmd[1])
	{
		ft_valid_quotes_aux0(var);
		while (node->cmd[1][var[0]])
		{
			ft_valid_quotes_aux1(node, c, var);
			if (var[2] != var[1])
			{
				ft_valid_quotes_aux2(sh, node, var);
				if (sh->ret < 0)
					return ;
			}
			else
			{
				if (var[3] && (ft_strncmp(first_c, "cd ", 4) == 0))
					sh->tmp1 = ft_strdup(".");
			}
		}
	}
}

static void	ft_valid_quotes_aux0(long *var)
{
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	var[3] = TRUE;
	var[4] = 0;
}

static void	ft_valid_quotes_aux1(t_node *node, int c, long *var)
{
	while (node->cmd[1][var[0]] && (node->cmd[1][var[0]] == c))
	{
		var[0]++;
		var[4]++;
	}
	if ((c == '\'') || (c == '\"'))
		var[4] = 0;
	var[1] = var[0];
	while (node->cmd[1][var[0]] && (node->cmd[1][var[0]] != c))
		var[0]++;
	var[2] = var[0];
}
