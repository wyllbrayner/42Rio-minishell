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

void	ft_expand_variable_0_aux_04(t_minishell *sh, long *var)
{
	var[1] = ft_strlen(sh->tmp1);
	var[0] = 0;
	var[3] = FALSE;
	ft_unset_aux_1(sh, var);
	if (var[3])
	{
		var[4] = ft_strchr_i(sh->env[var[2]], '=');
		sh->tmp5 = ft_substr(sh->env[var[2]], (var[4] + 1), \
		ft_strlen(sh->env[var[2]]) - var[4]);
	}
	else
	{
		if (ft_strncmp(sh->tmp1, "?=", 3) == 0)
			sh->tmp5 = ft_itoa(sh->errnbr);
		else
			sh->tmp5 = ft_strdup("");
	}
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
}

void	ft_expand_variable_0_aux_05(t_minishell *sh)
{
	if (!sh->tmp5)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp0, sh->tmp5);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		sh->ret = -3;
		sh->errnbr = errno;
	}
	sh->tmp5 = sh->tmp1;
	sh->tmp1 = NULL;
}

/*
//  export      TEST='$HOME'$PATH $PROJ 
    long    start;  // var[0];
    long    end;    // var[1];
    long    i_env;  // var[2];
    long    status; // var[3];
    long    len;        // var[4];
    long    j;          // var[5];
    long    quote;      // var[6];
// echo eu: $USER em: $PATH ou: ~ , falo: $LANG
//  echo      TEST='$HOME'$PATH$PROJ 
//  echo      TEST='$HOME'$PROJ $PATH 
//  echo      TEST=$?$HOME'$PROJ' $PATH
//  echo      TEST='$HOME'$PATH' ' $USER
//  echo      TEST=$?$HOME'$PROJ' '$PATH'''
//  echo    $HOME~ TEST='$HOME'  $PATH' ' ~ $USER // loop infinito
//  ls $HOME~ ~/projetos   
// ls "$HOME" | exit | echo "sair daqui | agora"
// echo "'''''$HOME'''''" | e''xi''t | echo "'''sair daqui | agora'''" 
// | ls "''''$HOME''''"/PROJETOS
// tmp0 = null
// tmp1 = null
// tmp2 = null
// tmp5 = ls /home/wyllbrayner /projetosNULL
//                    [0]
//                    [5]
//  00000000001111111111222222
//  01234567890123456789012345
//  ls $HOME~ /projetos 
*/
