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

#include "../../header/ft_minishell.h"

extern t_signal	g_sig;

static void	ft_unset_aux_2(t_minishell *sh, long i);
static void	ft_unset_aux_3(t_minishell *sh, long i);

void	ft_builtin_unset(t_minishell *sh, t_node *node)
{
	long	var[4];

	var[0] = ft_strchr_i(node->token, ' ');
	if (var[0] != 0)
	{
		var[1] = ft_strlen(node->token);
		sh->tmp1 = ft_substr(node->token, (var[0] + 1), (var[1] - var[0] - 1));
		sh->tmp2 = ft_strjoin(sh->tmp1, "=");
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
		sh->tmp1 = sh->tmp2;
		sh->tmp2 = NULL;
		var[3] = FALSE;
		ft_unset_aux_1(sh, var);
		if (var[3])
		{
			ft_unset_aux_2(sh, var[2]);
			if (sh->ret < 0)
				return ;
		}
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
	}
	g_sig.errnbr = 0;
}

void	ft_unset_aux_1(t_minishell *sh, long *var)
{
	var[2] = 0;
	while (sh->env[var[2]])
	{
		if (ft_strncmp(sh->env[var[2]], sh->tmp1, ((var[1]) - var[0])) == 0)
		{
			var[3] = TRUE;
			break ;
		}
		var[2] = var[2] + 1;
	}
}

static void	ft_unset_aux_2(t_minishell *sh, long i)
{
	long	len;

	len = 0;
	while (sh->env[len])
		len++;
	sh->tmp3 = (char **)malloc(sizeof(char *) * len);
	if (!sh->tmp3)
	{
		g_sig.errnbr = errno;
		ft_free_minishell_single_aux(sh->tmp1);
		sh->tmp1 = NULL;
		sh->ret = -3;
		return ;
	}
	sh->tmp3[--len] = NULL;
	ft_unset_aux_3(sh, i);
	ft_free_minishell_double_aux(sh->env);
	sh->env = NULL;
	sh->env = sh->tmp3;
	sh->tmp3 = NULL;
	ft_free_minishell_double_aux(sh->tmp3);
	sh->tmp3 = NULL;
}

static void	ft_unset_aux_3(t_minishell *sh, long i)
{
	long	j;
	long	k;

	j = 0;
	k = 0;
	while (sh->env[j])
	{
		if (j != i)
		{
			sh->tmp3[k] = sh->env[j];
			k++;
		}
		else
			ft_free_minishell_single_aux(sh->env[j]);
		sh->env[j] = NULL;
		j++;
	}
}
