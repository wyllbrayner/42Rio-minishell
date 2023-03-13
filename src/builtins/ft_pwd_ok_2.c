/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:21:29 by jodiniz           #+#    #+#             */
/*   Updated: 2023/01/20 10:21:29 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"

void	ft_builtin_pwd(t_minishell *sh)
{
	sh->tmp1 = getcwd(NULL, 0);
	if (!sh->tmp1)
	{
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	ft_putendl_fd(sh->tmp1, STDOUT_FILENO);
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	sh->errnbr = 0;
}
