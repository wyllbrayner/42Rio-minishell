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

static void	ft_expander_dquote(t_minishell *sh, t_node *node);
static void	ft_expander_squote(t_minishell *sh, t_node *node);
static void	ft_expander_squote_aux_0(t_minishell *sh, t_node *node, long *var);

//printf("Dentro da ft_expander_quote - Início\n");
//printf("Antes de ft_expand_variable_dquote, node->token: %s\n", node->token);
//printf("Após     ft_expand_variable_dquote, node->token: %s\n", node->token);
//printf("===================================================\n");
//printf("Antes de ft_expand_variable_squote, node->token: %s\n", node->token);
//printf("Após     ft_expand_variable_squote, node->token: %s\n", node->token);
//printf("Dentro da ft_expander_quote - Fim\n");

/*
//  export      TEST='$HOME'$PATH $PROJ 
    long    start;  // var[0];
    long    end;    // var[1];
    long    i_env;  // var[2];
    long    status; // var[3];
    long    len;        // var[4];
    long    j;          // var[5];
    long    quote;      // var[6];
//  echo      TEST='$HOME'$PATH$PROJ 
//  echo      TEST='$HOME'$PROJ $PATH 
//  echo      TEST=$?$HOME'$PROJ' $PATH
//  echo      TEST='$HOME'$PATH' ' $USER
//  echo      TEST=$?$HOME'$PROJ' '$PATH'''
//  echo    $HOME~ TEST='$HOME'  $PATH' ' ~ $USER // loop infinito
//  ls $HOME~ ~/projetos   
// ls "$HOME" | exit | echo "sair daqui | agora"
// echo "'''''$HOME'''''" | e''xi''t | echo "'''sair daqui | agora'''" 
| ls "''''$HOME''''"/PROJETOS
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
void	ft_expander_quote(t_minishell *sh, t_node *node)
{
	ft_expander_dquote(sh, node);
	if (sh->ret < 0)
		return ;
	ft_expander_squote(sh, node);
	if (sh->ret < 0)
		return ;
}

static void	ft_expander_dquote(t_minishell *sh, t_node *node)
{
	long	i;
	long	j;

	i = 0;
	j = 0;
	sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1));
	if (!sh->tmp1)
	{
		sh->errnbr = errno;
		sh->ret = -3;
	}
	else
	{
		while (node->token[i])
		{
			if (node->token[i] != '\"')
				sh->tmp1[j++] = node->token[i];
			i++;
		}
		sh->tmp1[j] = '\0';
		ft_builtin_cd_aux_2(sh, node);
	}
}

static void	ft_expander_squote(t_minishell *sh, t_node *node)
{
	long	var[3];

	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	sh->tmp1 = (char *)malloc(sizeof(char) * (ft_strlen(node->token) + 1));
	if (!sh->tmp1)
	{
		sh->errnbr = errno;
		sh->ret = -3;
	}
	else
	{
		ft_expander_squote_aux_0(sh, node, var);
		sh->tmp1[var[1]] = '\0';
		ft_builtin_cd_aux_2(sh, node);
	}
}

static void	ft_expander_squote_aux_0(t_minishell *sh, t_node *node, long *var)
{
	while (node->token[var[0]])
	{
		while (node->token[var[0]])
		{
			if (node->token[var[0]] == '\'')
			{
				var[0]++;
				var[2]++;
			}
			else
				break ;
		}
		if (var[2] % 2)
			sh->tmp1[var[1]++] = '\'';
		var[2] = 0;
		while (node->token[var[0]])
		{
			if (node->token[var[0]] != '\'')
				sh->tmp1[var[1]++] = node->token[var[0]];
			else
				break ;
			var[0]++;
		}
	}
}
