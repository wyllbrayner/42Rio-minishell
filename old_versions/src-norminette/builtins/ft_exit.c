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
		if (sh->s_int == 1)
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
		sh->errnbr = 0;
}

static void	ft_builtin_exit_aux_0(t_minishell *sh, t_node *node)
{
	sh->ret = -9;
	sh->erro = node->cmd[0];
	sh->errnbr = 1;
	sh->running = TRUE;
}

//    printf("Dentro da exit - Início\n");
//        printf("errnbr: %i\n", sh->errnbr);
//                printf("errnbr: %i\n", sh->errnbr);
//        printf("errnbr: %i\n", sh->errnbr);
//        printf("errnbr: %i\n", sh->errnbr);
//    printf("errnbr: %i\n", sh->errnbr);
//    printf("Dentro da exit - Fim\n");
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
			sh->errnbr = 255;
			return ;
		}
		i++;
	}
	sh->errnbr = ft_atoi(node->cmd[1]);
	if (sh->errnbr >= 0)
		sh->errnbr = sh->errnbr % 256;
	else
		sh->errnbr = ft_exit_return(sh->errnbr);
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
