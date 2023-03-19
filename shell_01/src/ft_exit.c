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

static void	ft_builtin_exit_aux_0(t_minishell *sh, t_node *node);
static void	ft_builtin_exit_aux_1(t_minishell *sh, t_node *node);
static int	ft_exit_return(int nbr);

void	ft_builtin_exit(t_minishell *sh, t_node *node)
{
	long	i;

	i = 0;
	while (node->cmd[i])
		i++;
	if (!node->prev && !node->next)
	{
		if (g_sig.s_int == 1)
			ft_putendl_fd("exit", STDOUT_FILENO);
		sh->running = FALSE;
	}
	if (i >= 3)
		ft_builtin_exit_aux_0(sh, node);
	else if (i == 2)
	{
		ft_builtin_exit_aux_1(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else
		g_sig.errnbr = 0;
}

static void	ft_builtin_exit_aux_0(t_minishell *sh, t_node *node)
{
	sh->ret = -9;
	sh->erro = node->cmd[0];
	g_sig.errnbr = 1;
	sh->running = TRUE;
}

static void	ft_builtin_exit_aux_1(t_minishell *sh, t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd[1][i])
	{
		if (!ft_strchr("+-0123456789", node->cmd[1][i]))
		{
			sh->ret = -11;
			sh->erro = node->cmd[1];
			g_sig.errnbr = 255;
			return ;
		}
		i++;
	}
	g_sig.errnbr = ft_atoi(node->cmd[1]);
	if (g_sig.errnbr >= 0)
		g_sig.errnbr = g_sig.errnbr % 256;
	else
		g_sig.errnbr = ft_exit_return(g_sig.errnbr);
}

static int	ft_exit_return(int nbr)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	nbr = nbr * (-1);
	while (total <= nbr)
	{
		total = (i * 256);
		i++;
	}
	return (total - nbr);
}
