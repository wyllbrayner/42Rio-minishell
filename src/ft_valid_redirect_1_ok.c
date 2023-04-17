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

static int	ft_valid_redirect_1_aux_0(t_minishell *sh, long *var);

void	ft_valid_redirect_1(t_minishell *sh)
{
	long	var[5];

	ft_cmd_builder_init_var(sh->caract, "><", var);
	while (sh->line[var[0]])
	{
		if (ft_valid_redirect_1_aux_0(sh, var))
			break ;
	}
}

static int	ft_valid_redirect_1_aux_0(t_minishell *sh, long *var)
{
	ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
	if (sh->line[var[0]])
		var[0]++;
	else
		return (1);
	while (sh->line[var[0]])
	{
		if (ft_isspace(sh->line[var[0]]))
			var[0]++;
		else
			return (1);
	}
	if (sh->line[var[0]] == '|')
	{
		sh->ret = -6;
		sh->erro = "|";
		g_sig.errnbr = 258;
		return (1);
	}
	if (sh->line[var[0]])
		var[0]++;
	return (0);
}
