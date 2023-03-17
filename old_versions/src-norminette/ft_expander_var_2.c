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

//    printf("Dentro da ft_interpreter - Início erronbr: %i\n", sh->errnbr);
//    printf("Dentro da ft_interpreter - Fim\n");

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

/*
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
    printf("Dentro da ft_expand_variable_0 - Início errnbr: %i\n", sh->errnbr);
*/
//  printf("Dentro do if   tmp0: %s#\n", sh->tmp0);
//            printf("Dentro do else   tmp0: %s#\n", sh->tmp0);
// printf("Dentro do else, join de tmp5: %s# e tmp0: %s# em tmp1: %s#
// n", sh->tmp5, sh->tmp0, sh->tmp1);
// printf("Dentro do else, troca os ponteiros de tmp0: %s# e tmp1: %s#\n",
//        sh->tmp0, sh->tmp1);
/*
    printf("Após os ifs\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/
//  printf("Após colocar o histórico tmp0 v[0] recebe v[5] -> v[0]: %ld; v[1]: 
//  %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], 
//  var[1], var[2], var[3], var[4], var[5], var[6]);
//  printf("Andou até o próximo '$~/\' (espaço)'        -> v[0]: %ld; 
//  v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", 
//  var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//            printf("é ~\n");
//            printf("é ~\n");
//  printf("malloca len: %ld posições a partir de: var[0]: %ld até var[5]: 
//  %ld -> tmp5: %s\n", (var[5] - var[0]), var[0], var[5], sh->tmp5);
//        printf("sh->tmp5 não conseguiu mallocar\n");
// printf("join de tmp5: %s com = em tmp1: %s\n", sh->tmp5, sh->tmp1);
//        printf("sh->tmp1 não conseguiu mallocar\n");
//    printf("Antes de ft_unset_aux_1                        -> v[0]: %ld; 
//    v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", 
//    var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//	ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
//    printf("Após     ft_unset_aux_1                        -> v[0]: %ld; 
//    v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", 
//    var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
// printf("ft_unset_aux_1 retornou true e tmp2: %s\n", sh->tmp2);
// printf("ft_unset_aux_1 retornou false, mas tmp1 = $?=: %s\n", sh->tmp2);
// printf("ft_unset_aux_1 retornou false, mas tmp5 = $?=: %s\n", sh->tmp5);
// printf("ft_unset_aux_1 retornou false, malloca espaço: #%s#\n", sh->tmp2);
/*
    printf("Dentro da ft_expand_variable_0 - Fim\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/

static void	ft_expand_variable_0_aux_00(t_minishell *sh, t_node *node, \
		long *var)
{
	sh->tmp0 = ft_substr(node->token, var[0], (var[5] - var[0]));
	if (!sh->tmp0)
	{
		ft_free_minishell_single_aux(sh->tmp5);
		sh->tmp5 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp5, sh->tmp0);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		sh->errnbr = errno;
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
			sh->errnbr = errno;
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
		sh->errnbr = errno;
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
		sh->errnbr = errno;
		return ;
	}
}
