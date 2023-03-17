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

//    printf("Dentro da valid_redirect 0 -> Início\n");
//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
//printf("Dentro da valid_redirect 0 -> loop\n");
//printf("Dentro da valid_redirect 0 -> loop após aux_0 var[0]: %ld\n",var[0]);
//    printf("Dentro da valid_redirect 0 -> Fim\n");
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
		sh->errnbr = 258;
		return (1);
	}
	if (sh->line[var[0]])
		var[0]++;
	return (0);
}
