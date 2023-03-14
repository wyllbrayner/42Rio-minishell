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

static int	ft_valid_lexcal_cmd_aux_0(t_minishell *sh, t_node *tmp);
static int	ft_valid_lexcal_cmd_aux_1(t_minishell *sh, t_node *tmp);

//    printf("Dentro da ft_valid_lexcal_cmd -> Início - 
//    errnbr: %i\n", sh->errnbr);
//    printf("Dentro da ft_valid_lexcal_cmd -> Fim - 
//    errnbr: %i\n", sh->errnbr);
void	ft_valid_lexcal_cmd(t_minishell *sh)
{
	t_node	*tmp;
	int		tmp_ret;

	tmp = sh->head;
	sh->ret = -6;
	sh->erro = "|";
	tmp_ret = 0;
	if (sh->errnbr != 0)
		tmp_ret = sh->errnbr;
	sh->errnbr = 258;
	while (tmp)
	{
		if (ft_valid_lexcal_cmd_aux_0(sh, tmp))
			return ;
		if (ft_valid_lexcal_cmd_aux_1(sh, tmp))
			return ;
		tmp = tmp->next;
	}
	sh->ret = 0;
	sh->erro = NULL;
	sh->errnbr = tmp_ret;
}

static int	ft_valid_lexcal_cmd_aux_0(t_minishell *sh, t_node *tmp)
{
	if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
		return (1);
	if ((!tmp->next) && (tmp->cmd[0][0] == '|'))
		return (1);
	if ((!tmp->next) && (tmp->cmd[0][0] == '>'))
	{
		sh->erro = NULL;
		return (1);
	}
	if ((tmp->cmd[0][0] == '|') && (tmp->next))
	{
		if (!tmp->next->cmd[0])
			return (1);
		if (tmp->next->cmd[0][0] == '|')
			return (1);
	}
	return (0);
}

static int	ft_valid_lexcal_cmd_aux_1(t_minishell *sh, t_node *tmp)
{
	if ((tmp->cmd[0][0] == '>') && (tmp->next))
	{
		if (!tmp->next->cmd[0])
			return (1);
		if (tmp->next->cmd[0][0] == '>')
		{
			sh->erro = ">";
			return (1);
		}
	}
	return (0);
}
