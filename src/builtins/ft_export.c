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

//    printf("Dentro da export\n");
//    printf("node->token: %s\n", node->token);
//        printf("node->cmd[1]: %s | start %d | end: %ld\n", node->cmd[1], 0,
// end);
//            printf("Dentro da export | start: %d | end: %ld | sub_str: %s\n",
// 0, end, sh->tmp1);
//                printf("    Achei a variável de ambiente: %s em env[%ld]: 
//%s\n", sh->tmp1, i, sh->env[i]);
//            sh->env[i] = ft_substr(node->cmd[1], (end + 1), 
//(ft_strlen(node->cmd[1]) - (end + 1))); //
//                printf("Não achei a variável de ambiente: %s em env[%ld]: 
//%s\n", sh->tmp1, i, sh->env[i]);
//                printf("Total de variáveis de ambiente: %ld\n", i);

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
			printf("declare -x %s\n", sh->env[var[0]++]);
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

//	sh->tmp1 = ft_substr(node->cmd[1], 0, var[1]);
//		if (ft_strncmp(sh->env[var[0]], sh->tmp1, var[1]) == 0)
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

/*
void	ft_builtin_export(t_minishell *sh, t_node *node)
{
	long	i;
	long	end;
	long	status;

	if (node->cmd[1])
	{
		ft_single_and_double_quotes(sh, node, "export ");
		end = ft_strchr_i(node->cmd[1], '=');
		if (end)
		{
			sh->tmp1 = ft_substr(node->cmd[1], 0, end);
			i = 0;
			status = FALSE;
			while (sh->env[i])
			{
				if (ft_strncmp(sh->env[i], sh->tmp1, end) == 0)
				{
					status = TRUE;
					break ;
				}
				i++;
			}
			if (status)
			{
				ft_free_minishell_single_aux(sh->env[i]);
				sh->env[i] = NULL;
				sh->env[i] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1]));
			}
			else
			{
				i++;
				sh->tmp3 = (char **)malloc(sizeof(char *) * (++i));
				if (!sh->tmp3)
				{
					sh->errnbr = errno;
					ft_free_minishell_single_aux(sh->tmp1);
					sh->ret = -3;
					return ;
				}
				sh->tmp3[--i] = NULL;
				sh->tmp3[--i] = ft_substr(node->cmd[1], 0, ft_strlen(node->cmd[1]));
				while (--i >= 0)
				{
					sh->tmp3[i] = sh->env[i];
					sh->env[i] = NULL;
				}
				ft_free_minishell_double_aux(sh->env);
				sh->env = NULL;
				sh->env = sh->tmp3;
			}
			ft_free_minishell_single_aux(sh->tmp1);
			sh->tmp1 = NULL;
			sh->tmp3 = NULL;
		}
	}
	else
	{
		i = 0;
		while (sh->env[i])
			printf("declare -x %s\n", sh->env[i++]);
	}
	sh->errnbr = 0;
}
*/
