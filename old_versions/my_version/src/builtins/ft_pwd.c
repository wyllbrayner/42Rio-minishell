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

void	ft_builtin_pwd(t_minishell *sh)
{
	sh->tmp1 = getcwd(NULL, 0);
	if (!sh->tmp1)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	ft_putendl_fd(sh->tmp1, STDOUT_FILENO);
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	g_sig.errnbr = 0;
}
